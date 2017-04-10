                                /*******************************************************************************
 * Copyright (C) 2013 Spansion LLC. All Rights Reserved.
 *
 * This software is owned and published by:
 * Spansion LLC, 915 DeGuigne Dr. Sunnyvale, CA  94088-3453 ("Spansion").
 *
 * BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
 * BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
 *
 * This software contains source code for use with Spansion
 * components. This software is licensed by Spansion to be adapted only
 * for use in systems utilizing Spansion components. Spansion shall not be
 * responsible for misuse or illegal use of this software for devices not
 * supported herein.  Spansion is providing this software "AS IS" and will
 * not be responsible for issues arising from incorrect user implementation
 * of the software.
 *
 * SPANSION MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
 * REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
 * ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
 * WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
 * WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
 * WARRANTY OF NONINFRINGEMENT.
 * SPANSION SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
 * LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
 * INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
 * SAVINGS OR PROFITS,
 * EVEN IF SPANSION HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
 * INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
 * FROM, THE SOFTWARE.
 *
 * This software may be replicated in part or whole for the licensed use,
 * with the restriction that this Disclaimer and Copyright notice must be
 * included with each copy of this software, whether used in part or whole,
 * at all times.
 */

/******************************************************************************/
/** \file lcd.c
 **
 ** Main Module
 **
 ** History:
 **   - 2013-03-21  0.0.1  MWi        First version.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mcu.h"
#include "registers.h"
#include "pins.h"
#include "glcdfont.h"



#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define WIDTH   480
#define HEIGHT  320


#define TOUCHXMIN   22 
#define TOUCHXMAX   220
#define TOUCHYMIN   50
#define TOUCHYMAX   192
#define TOUCHZMIN   5
#define TOUCHZMAX   185


/***
 *      GLOBAL VARIABLES
 ****/

int16_t cursorX = 0;
int16_t cursorY = 0;
uint16_t textColor = WHITE;
uint8_t textSize = 1;
int textBackground = BLACK;

struct TouchPoint{
  uint16_t x;
  uint16_t y;
  uint16_t z;
} touchPoint;

/**
 *  Delays the programm for the given time.
 *  @author Puria Izady
 *  @param millisecons length of delay
 */
void  delay(int milliseconds){
    volatile unsigned long u32Delay;
    for(u32Delay = milliseconds*450; u32Delay > 0; u32Delay--);
}

/**
 *  Returns the bit of the char d which is choosen by number.
 *  @author Puria Izady
 */
int  getBit(char data, int bitNumber) {
    return (data & (1 << bitNumber-1)) != 0;
}

/**
 *  Toggles between LCD_WR_ACTIVE and LCD_WRITE_IDLE.
 *  @author Puria Izady
 */
void writeStrobe(){
    LCD_WR = 0u;
    LCD_WR = 1u;
}

/**
 *  Writes 8 Bits parallel on the Data-Pins 0-7.
 *  @author Puria Izady
 *  @param char d - the 8 bit data
 */
void write8(char d) {
    LCD_D0 =  getBit(d,1);
    LCD_D1 =  getBit(d,2);
    LCD_D2 =  getBit(d,3);
    LCD_D3 =  getBit(d,4);
    LCD_D4 =  getBit(d,5);
    LCD_D5 =  getBit(d,6);
    LCD_D6 =  getBit(d,7);
    LCD_D7 =  getBit(d,8);
    
    writeStrobe();
}

/**
 *  Writes 32 Bits 4 times serial on the parallel Data-Pins 0-7.
 *  @author Puria Izady
 *  @param long d - the 32 bit data
 */
void write32(char r, long d) {
    LCD_CS = 0u;    // LCD_CS_ACTIVE
    LCD_CD = 0u;
    write8(r);
    LCD_CD = 1u;
    //delay(10);
    write8(d >> 24);
    //delay(10);
    write8(d >> 16);
    //delay(10);
    write8(d >> 8);
    //delay(10);
    write8(d);
    LCD_CS = 1u;    // LCD_CS_IDLE
}


/**
 *  Set Value of the TFT 8-bit registers aH and aL with the low and high parts of the 16 bit value d.
 *
 */
void writeRegisterPair(char aH, char aL, int d) {
    char hi = (d) >> 8, lo = (d);
    LCD_CD = 0u; write8(aH); LCD_CD = 1u; write8(hi);
    LCD_CD = 0u; write8(aL); LCD_CD = 1u; write8(lo);
}


/**
  *
  *    Writes command and data on 8-Data pins.
  */
void writeRegister8(char a, char d) {
    LCD_CD = 0u;
    write8(a);
    LCD_CD = 1u;
    write8(d);
}

/**
 *  Sets the Window of coordinates, that are going to be manipulated by a method.
 *  @author Puria Izady
 */
void setAddrWindow(int x1, int y1, int x2, int y2){
    LCD_CS = 0u;
    unsigned long t;
    
    t = x1;
    t <<= 16;
    t |= x2;
    write32(ILI9341_PAGEADDRSET, t);  // HX8357D uses same registers!    
    t = y1;
    t <<= 16;
    t |= y2;
    write32(ILI9341_COLADDRSET, t); // HX8357D uses same registers!                 
    LCD_CS = 1u;
}

/**
 * Initialization of the direction and start value of 8 data and 5 control pins
 * @author Puria Izady
 */
void init(){
    // Set LCD Data Pins orientation to output
    LCD_D0_IO  = 1u; // Direction: Output
    LCD_D1_IO  = 1u; // Direction: Output
    LCD_D2_IO  = 1u; // Direction: Output
    LCD_D3_IO  = 1u; // Direction: Output
    LCD_D4_IO  = 1u; // Direction: Output
    LCD_D5_IO  = 1u; // Direction: Output
    LCD_D6_IO  = 1u; // Direction: Output
    LCD_D7_IO  = 1u; // Direction: Output
    
    // Set all LCD Data Pins to LOW
    LCD_D1 = 0u;  // LCD_D0 => HIGH
    LCD_D0 = 0u;
    LCD_D7 = 0u;
    LCD_D6 = 0u;
    LCD_D5 = 0u;
    LCD_D4 = 0u;
    LCD_D3 = 0u;
    LCD_D2 = 0u;
    
    // SET ANALOG PINS TO DIGITAL
    bFM4_GPIO_ADE_AN00 = 1u;
    bFM4_GPIO_ADE_AN01 = 0;
    // bFM4_GPIO_ADE_AN02 = 0;
    bFM4_GPIO_ADE_AN03 = 1u;
    bFM4_GPIO_ADE_AN04 = 1u;
    bFM4_GPIO_ADE_AN16 = 1u;
    
    bFM4_GPIO_ADE_AN11 = 0;  // D0/P1B ANALOG OFF
    bFM4_GPIO_ADE_AN12 = 0;  // D1/P1C ANALOG OFF
    
    bFM4_GPIO_ADE_AN06 = 1u; // Xm/P16 ANALOG ON
    bFM4_GPIO_ADE_AN07 = 1u; // Yp/P17 ANALOG ON
    
    JS1_X_IO = 1u;
    JS1_Y_IO = 1u;
    JS2_X_IO = 1u;
    JS2_Y_IO = 1u;
    
    // SET LCD CONTROL PINS TO OUTPUT MODE
    LCD_RD_IO = 1u;
    LCD_WR_IO = 1u;
    LCD_CD_IO = 1u;
    LCD_CS_IO = 1u;
    LCD_RS_IO = 1u;
    
    
    // SET ALL LCD CONTROL PINS TO HIGH
    LCD_RD = 1u;
    LCD_WR = 1u;
    LCD_CD = 1u;
    LCD_CS = 1u;
    LCD_RS = 1u;
}

/**
 *  Resets the Display.
 *  @author Puria Izady
 */
void reset(){
    volatile unsigned long u32Delay;
    volatile unsigned long i;
    LCD_CS = 1u;    //LCD_CS_IDLE
    //  CD_DATA;
    LCD_WR = 1u;    // LCD_WR_IDLE
    LCD_RD = 1u;    // LCD_RD_IDLE
    
    LCD_RS = 0u;
    for(u32Delay = 1200000; u32Delay > 0; u32Delay--);    //delay(2);
    LCD_RS = 1u;
    
    // Data transfer sync
    LCD_CS = 0u;
    LCD_CD = 0u;
    write8(0x00);               // NOP COMMAND
    for(i=0; i<3; i++) {
        writeStrobe();    // Three extra 0x00s  // WR_STROBE = { LCD_WR = 0u; LCD_WR = 1u; }
    }
    LCD_CS = 1u;
}

/**
 *  Runs the configuration methods of the LCD-Controller.
 *  @author Puria Izady
 */
void setupLCD() {
    static const long HX8357D_regValues[] = {
        HX8357_SWRESET, 0,
        HX8357D_SETC, 3, 0xFF, 0x83, 0x57,
        TFTLCD_DELAY, 250,
        HX8357_SETRGB, 4, 0x00, 0x00, 0x06, 0x06,
        HX8357D_SETCOM, 1, 0x25,  // -1.52V
        HX8357_SETOSC, 1, 0x68,  // Normal mode 70Hz, Idle mode 55 Hz
        HX8357_SETPANEL, 1, 0x05,  // BGR, Gate direction swapped
        HX8357_SETPWR1, 6, 0x00, 0x15, 0x1C, 0x1C, 0x83, 0xAA,
        HX8357D_SETSTBA, 6, 0x50, 0x50, 0x01, 0x3C, 0x1E, 0x08,
        // MEME GAMMA HERE
        HX8357D_SETCYC, 7, 0x02, 0x40, 0x00, 0x2A, 0x2A, 0x0D, 0x78,
        HX8357_COLMOD, 1, 0x55,
        HX8357_MADCTL, 1, 0xC0,
        HX8357_TEON, 1, 0x00,
        HX8357_TEARLINE, 2, 0x00, 0x02,
        HX8357_SLPOUT, 0,
        TFTLCD_DELAY, 150,
        HX8357_DISPON, 0,
        TFTLCD_DELAY, 50,
    };
    volatile unsigned long u32Delay;
    volatile unsigned long i = 0;
    reset();
    delay(200);
    //for(u32Delay = 20000000; u32Delay > 0; u32Delay--);  // delay(200);
    
    LCD_CS = 0u; // LCD_CS_ACTIVE
    
    
    while(i < (sizeof(HX8357D_regValues) / (sizeof(HX8357D_regValues[0])) ) ) {
        volatile unsigned long r = HX8357D_regValues[i++];
        volatile unsigned long len = HX8357D_regValues[i++];
        if(r == TFTLCD_DELAY) {
            delay(len);
        } else {
            LCD_CS = 0u;    // LCD_CS_ACTIVE
            LCD_CD = 0u;
            write8(r);
            LCD_CD = 1u;
            volatile unsigned long d;
            for (d=0; d<len; d++) {
                volatile unsigned long x = HX8357D_regValues[i++];
                write8(x);
            }
            LCD_CS = 1u;    // LCD_CS_IDLE
        }
    }
    return;
}

/**
 *  Kind of a reset for setAddrWindow().
 *
 */
void setLR(void) {
    LCD_CS = 0u;
    writeRegisterPair(HX8347G_COLADDREND_HI, HX8347G_COLADDREND_LO, 480  - 1);    
    writeRegisterPair(HX8347G_ROWADDREND_HI, HX8347G_ROWADDREND_LO, 320 - 1);     
    LCD_CS = 1u;
}


/**
  *     Sets the rotation of the display.
  *
  */
void setRotation(char x){
  int _width, _height;  
  char rotation = (x & 3);
    switch(rotation) {
        case 0:
        case 2:
            _width  = WIDTH;
            _height = HEIGHT;
            break;
        case 1:
        case 3:
            _width  = HEIGHT;
            _height = WIDTH;
            break;
    }
    // MEME, HX8357D uses same registers as 9341 but different values
    uint16_t t;
     
    switch (rotation) {
        case 2:
            t = HX8357B_MADCTL_RGB;
            break;
        case 3:
            t = HX8357B_MADCTL_MX | HX8357B_MADCTL_MV | HX8357B_MADCTL_RGB;
            break;
        case 0:
            t = HX8357B_MADCTL_MX | HX8357B_MADCTL_MY | HX8357B_MADCTL_RGB;
            break;
        case 1:
            t = HX8357B_MADCTL_MY | HX8357B_MADCTL_MV | HX8357B_MADCTL_RGB;
            break;
    }
    writeRegister8(ILI9341_MADCTL, t ); // MADCTL
    // For 8357, init default full-screen address window:
    setAddrWindow(0, 0, _width - 1, _height - 1); // CS_IDLE happens here
}

 

/**
 *  Floods the GRAM len-times. 
 *  @author Puria Izady
 */
void flood(int color, long len){
    volatile unsigned int blocks;
    volatile unsigned char  i, hi = color >> 8,
    lo = color;
    
    LCD_CS = 0u;
    LCD_CD = 0u;
    write8(HX8357_RAMWR);
    
    
    // Write first pixel normally, decrement counter by 1
    LCD_CD = 1u;;
    write8(hi);
    write8(lo);
    len--;
    
    blocks = (volatile unsigned int) (len / 64); // 64 pixels/block
    if(hi == lo) {
        // High and low bytes are identical.  Leave prior data
        // on the port(s) and just toggle the write strobe.
        while(blocks--) {
            i = 16; // 64 pixels/block / 4 pixels/pass
            do {
                writeStrobe(); writeStrobe(); writeStrobe(); writeStrobe(); // 2 bytes/pixel
                writeStrobe(); writeStrobe(); writeStrobe(); writeStrobe(); // x 4 pixels
            } while(--i);
        }
        // Fill any remaining pixels (1 to 64)
        for(i = 63; i--; ) {
            writeStrobe();
            writeStrobe();
        }
    } else {
        while(blocks--) {
            i = 16; // 64 pixels/block / 4 pixels/pass
            do {
                write8(hi); write8(lo); write8(hi); write8(lo);
                write8(hi); write8(lo); write8(hi); write8(lo);
            } while(--i);
        }
        for(i = 63; i--; ) {
            write8(hi);
            write8(lo);
        }
    }
    LCD_CS = 1u;
    
}

/**
 *  Fills all the Screen with the given color.
 *  @author Puria Izady
 */
void fillScreen(int color){
    setAddrWindow(0, 0, 480 - 1, 320 - 1);
    flood(color, 480 * 320);
}


/**
 *      Sets the Cursor coordinate.
 */
void setCursor(int16_t x, int16_t y) {
    cursorX = x;
    cursorY = y;
}

/**
 *      Sets the global text color.
 */
void setTextColor(uint16_t c) {
    // For 'transparent' background, we'll set the bg
    // to the same as fg instead of using a flag
    textColor = c;
}

/**
 *      Sets the global text size.
 */
void setTextSize(uint8_t s) {
    textSize = (s > 0) ? s : 1;
}

/**
 *    Sets the background color for the text.
 */
void setBackgroundColor(int bg){
  textBackground = bg;
}



/**
 *  Draws a horizontal line starting at (x,y) and ending at (x+length,y)
 *  @author Puria Izady
 */
void drawFastHLine(int x, int y, int length, int color) {
    int _width = WIDTH;
    int _height = HEIGHT;
    int x2;
    
    // Initial off-screen clipping
    if((length <= 0     ) ||
       (y      <  0     ) || ( y                  >= _height) ||
       (x      >= _width) || ((x2 = (x+length-1)) <  0      )) return;
    
    if(x < 0) {        // Clip left
        length += x;
        x       = 0;
    }
    if(x2 >= _width) { // Clip right
        x2      = _width - 1;
        length  = x2 - x + 1;
    }
    
    setAddrWindow(x, y, x2, y);
    flood(color, length);
    setLR();
}

/**
 *  Draws a Vertical line starting at (x,y) and ending at (x,y+length).
 *  @author Puria Izady
 */
void drawFastVLine(int x, int y, int length, int color) {
    int _width = WIDTH;
    int _height = HEIGHT;
    int y2;
    
    // Initial off-screen clipping
    if((length <= 0      ) ||
       (x      <  0      ) || ( x                  >= _width) ||
       (y      >= _height) || ((y2 = (y+length-1)) <  0     )) return;
    if(y < 0) {         // Clip top
        length += y;
        y       = 0;
    }
    if(y2 >= _height) { // Clip bottom
        y2      = _height - 1;
        length  = y2 - y + 1;
    }
    
    setAddrWindow(x, y, x, y2);
    flood(color, length);
    setLR();
}

/**
 *  Draw a rectangle
 */
void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    drawFastHLine(x, y, w, color);
    drawFastHLine(x, y+h-1, w, color);
    drawFastVLine(x, y, h, color);
    drawFastVLine(x+w-1, y, h, color);
}

/**
 *  Draws a filled rectangle at (x,y) to (x+w,y+h).
 */

void fillRect(int x1, int y1, int w, int h, int fillcolor) {
    int _width = WIDTH;
    int _height = HEIGHT;
    int  x2, y2;
    
    // Initial off-screen clipping
    if( (w            <= 0     ) ||  (h             <= 0      ) ||
       (x1           >= _width) ||  (y1            >= _height) ||
       ((x2 = x1+w-1) <  0     ) || ((y2  = y1+h-1) <  0      )) return;
    if(x1 < 0) { // Clip left
        w += x1;
        x1 = 0;
    }
    if(y1 < 0) { // Clip top
        h += y1;
        y1 = 0;
    }
    if(x2 >= _width) { // Clip right
        x2 = _width - 1;
        w  = x2 - x1 + 1;
    }
    if(y2 >= _height) { // Clip bottom
        y2 = _height - 1;
        h  = y2 - y1 + 1;
    }
    
    setAddrWindow(x1, y1, x2, y2);
    flood(fillcolor, (long)w * (long)h);
    setLR();
}

/**
 * Draws a Pixel at (x,y) with the wished color.
 */
void drawPixel(int16_t x, int16_t y, uint16_t color) {
    int _width = WIDTH;
    int _height = HEIGHT;
    // Clip
    if((x < 0) || (y < 0) || (x >= _width) || (y >= _height)) return;
    
    LCD_CS = 0u;
 
    setAddrWindow(x, y, _width-1, _height-1);
    LCD_CS = 0u;
    LCD_CD = 0u;
    write8(0x2C);
    LCD_CD = 1u;
    write8(color >> 8); write8(color);
    
    LCD_CS = 1u;
}

/**
 *      Only draw a char without Cursor.
 */
void drawChar(int x, int y,  char c,  int color,  int bg, char size) {
    int width = WIDTH;
    int height = HEIGHT;
    if((x >= 480)            || // Clip right
       (y >= 320)           || // Clip bottom
       ((x + 6 * size - 1) < 0) || // Clip left
       ((y + 8 * size - 1) < 0))   // Clip top
        return;
    
    //if(!_cp437 && (c >= 176)) c++; // Handle 'classic' charset behavior
    char i, j;
    for(i=0; i<6; i++ ) {  // draw in X-Richtung
        char line;  // was macht das?
        if(i < 5) line = font[(c*5)+i];  // rausfinden ob der Buchstabe an (i,j) einen Pixel hat
        
        else      line = 0x0;
        for(j=0; j<8; j++, line >>= 1) {  // draw in Y-Richtung
            if(line & 0x1) {
                if(size == 1) drawPixel(x+i, y-j, color);
                else          fillRect(x+(i*size), y-(j*size), size, size, color);
            } else if(bg != color) {
                if(size == 1) drawPixel(x+i, y-j, bg);
                else          fillRect(x+i*size, y-j*size, size, size, bg);
            }
        }
    }
}

  

/*
 *      GFX OBJECTS. CIRCLES, TRIANGLES, FONTS.
 */

/**
 *      Write a character with changing the cursor position.
 *
 */
void write(char c, int *cursor_x, int *cursor_y, char textsize,  int textcolor,  int bg) {
    if(c == '\n') {
        *cursor_y -= textsize*8;
        *cursor_x  = 0;
    } else if(c == '\r') {
        // skip em
    } else {
        if(((*cursor_x + textsize * 6) >= 480)) { // Heading off edge?
            *cursor_x  = 0;            // Reset x to zero
            *cursor_y -= textsize * 8; // Advance y one line
        }

        drawChar(*cursor_x ,*cursor_y , c, textcolor, bg, textsize);
        *cursor_x += textsize * 6;
    }
}


/**
 *      Write a character with automatic cursor.
 *
 */
void writeAuto(char c) {
    if(c == '\n') {
        cursorY -= textSize*8;
        cursorX  = 0;
    } else if(c == '\r') {
        // skip em
    } else {
        if(((cursorX + textSize * 6) >= 480)) { // Heading off edge?
            cursorX  = 0;            // Reset x to zero
            cursorY -= textSize * 8; // Advance y one line
        }

        drawChar(cursorX ,cursorY , c, textColor, textBackground, textSize);
        cursorX += textSize * 6;
    }
}

/**
 *    Write a char array with a linebreak.
 */
void writeText(char *text){
    int i;
    for(i = 0; text[i] != 0; i++){
        writeAuto(text[i]); 
    }
}

/**
 *    Write a char array with a linebreak.
 */
void writeTextln(char *text){
    int i;
    for(i = 0; text[i] != 0; i++){
        writeAuto(text[i]); 
    }
    cursorY -= textSize*8;
    cursorX  = 0;
}


/**
 *      Draw a circle outline.
 */
void drawCircle(int x0, int y0, int r, unsigned int color) {
    int f = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x = 0;
    int y = r;
    
    drawPixel(x0  , y0+r, color);
    drawPixel(x0  , y0-r, color);
    drawPixel(x0+r, y0  , color);
    drawPixel(x0-r, y0  , color);
    
    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        
        drawPixel(x0 + x, y0 + y, color);
        drawPixel(x0 - x, y0 + y, color);
        drawPixel(x0 + x, y0 - y, color);
        drawPixel(x0 - x, y0 - y, color);
        drawPixel(x0 + y, y0 + x, color);
        drawPixel(x0 - y, y0 + x, color);
        drawPixel(x0 + y, y0 - x, color);
        drawPixel(x0 - y, y0 - x, color);
    }
}

/**
 *      Special circles.
 */
void drawCircleHelper( int x0, int y0, int r, char cornername, unsigned int color) {
    int f     = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x     = 0;
    int y     = r;
    
    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x4) {
            drawPixel(x0 + x, y0 + y, color);
            drawPixel(x0 + y, y0 + x, color);
        }
        if (cornername & 0x2) {
            drawPixel(x0 + x, y0 - y, color);
            drawPixel(x0 + y, y0 - x, color);
        }
        if (cornername & 0x8) {
            drawPixel(x0 - y, y0 + x, color);
            drawPixel(x0 - x, y0 + y, color);
        }
        if (cornername & 0x1) {
            drawPixel(x0 - y, y0 - x, color);
            drawPixel(x0 - x, y0 - y, color);
        }
    }
}


/** 
 *   Used to do circles and roundrects
 */
void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) {
    
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;
    
    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        
        if (cornername & 0x1) {
            drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
            drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
        }
        if (cornername & 0x2) {
            drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
            drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
        }
    }
}

/**
 *      Draw a filled circle.
 */
void fillCircle(int x0, int y0, int r, unsigned int color) {
    drawFastVLine(x0, y0-r, 2*r+1, color);
    fillCircleHelper(x0, y0, r, 3, 0, color);
}

/**
 *      Draw a round rectangle.
 */
void drawRoundRect(int x, int y, int w, int h, int r, unsigned int color) {
    // smarter version
    drawFastHLine(x+r  , y    , w-2*r, color); // Top
    drawFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
    drawFastVLine(x    , y+r  , h-2*r, color); // Left
    drawFastVLine(x+w-1, y+r  , h-2*r, color); // Right
    // draw four corners
    drawCircleHelper(x+r    , y+r    , r, 1, color);
    drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
    drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
    drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}

/**
 *      Filled round rectangle.
 */
void fillRoundRect(int x, int y, int w, int h, int r, unsigned color) {
    // smarter version
    fillRect(x+r, y, w-2*r, h, color);
    
    // draw four corners
    fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
    fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}

/**
 *      Draw a line with bresenham algorithm.
 */
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        int16_t temp = x0;
        x0 = y0;
        y0 = temp;
        //_swap_int16_t(x0, y0);
        temp = x1;
        x1 = y1;
        y1 = temp;
        //_swap_int16_t(x1, y1);
    }
    
    if (x0 > x1) {
        int16_t temp = x0;
        x0 = x1;
        x1 = temp;
        //_swap_int16_t(x0, x1);
        temp = y0;
        y0 = y1;
        y1 = temp;
        //_swap_int16_t(y0, y1);
    }
    
    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);
    
    int16_t err = dx / 2;
    int16_t ystep;
    
    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }
    
    for (; x0<=x1; x0++) {
        if (steep) {
            drawPixel(y0, x0, color);
        } else {
            drawPixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

/**
 *      Draw a triangle
 */
void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    drawLine(x0, y0, x1, y1, color);
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x0, y0, color);
}

/**
 *      Fill a triangle
 */
void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    
    int16_t a, b, y, last;
    
    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) {
        int16_t temp = y0;
        y0 = y1;
        y1 = temp;
        temp = x0;
        x0 = x1;
        x1 = temp;
    }
    if (y1 > y2) {
        int16_t temp = y1;
        y1 = y2;
        y2 = temp;
        temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if (y0 > y1) {
        int16_t temp = y0;
        y0 = y1;
        y1 = y0;
        temp = x0;
        x0 = x1;
        x1 = temp;
    }
    
    if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
        a = b = x0;
        if(x1 < a)      a = x1;
        else if(x1 > b) b = x1;
        if(x2 < a)      a = x2;
        else if(x2 > b) b = x2;
        drawFastHLine(a, y0, b-a+1, color);
        return;
    }
    
    int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1;
    int32_t
    sa   = 0,
    sb   = 0;
    
    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if(y1 == y2) last = y1;   // Include y1 scanline
    else         last = y1-1; // Skip it
    
    for(y=y0; y<=last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        /* longhand:
         a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
         b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
         */
        if(a > b) {
          int16_t temp = a;
          a = b;
          b = temp;                   
        }
        drawFastHLine(a, y, b-a+1, color);
    }
    
    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y<=y2; y++) {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        /* longhand:
         a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
         b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
         */
        if(a > b) {
          int16_t temp = a;
          a = b;
          b = temp;
        }
        drawFastHLine(a, y, b-a+1, color);
    }
}

/**
 * Converts RGB to HEX.
 */
color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}



/**
 *
 */


/*
 *      BMP IMAGES
 */


/**
 * Issues 'raw' an array of 16-bit color values to the LCD.
 */
void pushColors(int *data, char len, char first) {
    int color;
    char  hi, lo;
    LCD_CS = 0u;
    if(first != 0) { // Issue GRAM write command only on first call
        LCD_CD = 0u;
        write8(0x2C);
    }
    LCD_CD = 1u;
    while(len--) {
        color = *data++;
        hi    = color >> 8; // Don't simplify or merge these
        lo    = color;      // lines, there's macro shenanigans
        write8(hi);         // going on.
        write8(lo);
    }
    LCD_CS = 1u;
}


/**
 *  Draw BMP Image.
 *  @author Puria Izady
 */
void bmpDraw(){
}


/*
 *      TOUCH SCREEN FUNCTIONS
 */

/**
 *  Read X-Coordinate
 */     
void NOTUSEDreadTouchX() {
  
    int samples[2];
    int i;

    TOUCH_YP_IO = 0u;   //    pinMode(_yp, INPUT);
    TOUCH_YM_IO = 0u;   //    pinMode(_ym, INPUT);
    TOUCH_YP = 0u;      //    digitalWrite(_yp, LOW);
    TOUCH_YM = 0u;      //    digitalWrite(_ym, LOW);

    TOUCH_XP_IO = 1u;   //    pinMode(_xp, OUTPUT);
    TOUCH_XP = 1u;      //    digitalWrite(_xp, HIGH);
    TOUCH_XM_IO = 1u;   //    pinMode(_xm, OUTPUT);
    TOUCH_XM = 0u;      //    digitalWrite(_xm, LOW);
     
    //getAnalogValues(&analog0, &analog3, &analog4, &analog6, &analog7, &analog16,&analog17);
    //char text[] = "Die X-Koordinate ist: ";
    //writeText(&text);
    //write8BitValueOnLCD(&analog7);
    /*
     * DOUBLE SAMPLING
     */
    /*
    for (i=0; i<2; i++) {
        samples[i] = analogRead(_yp);
    }
    
    if (samples[0] - samples[1] < -4 || samples[0] - samples[1] > 4) {
        valid = 0;
    } else {
        samples[1] = (samples[0] + samples[1]) >> 1; // average 2 samples
    }
    
    
    return (1023-samples[1]);
    */
}

/**
 *  Read Y-Coordinate
 */
int NOTUSEDreadTouchY() {

    //int samples[2];

    TOUCH_YP_IO = 1u;   //    pinMode(_yp, OUTPUT);
    TOUCH_YM_IO = 1u;   //    pinMode(_ym, OUTPUT);
    bFM4_GPIO_ADE_AN07 = 0u;  // ANALOG 7 OFF
    TOUCH_YP = 0u;      //    digitalWrite(_yp, LOW);
    TOUCH_YM = 0u;      //    digitalWrite(_ym, LOW);
    TOUCH_YP_IO = 0u;   //    pinMode(_yp, INPUT);
    TOUCH_YM_IO = 0u;   //    pinMode(_ym, INPUT);

    TOUCH_XP_IO = 1u;   //    pinMode(_xp, OUTPUT);
    TOUCH_XP = 1u;      //    digitalWrite(_xp, HIGH);
    TOUCH_XM_IO = 1u;   //    pinMode(_xm, OUTPUT);
    bFM4_GPIO_ADE_AN06 = 0u; // Xm/P16 ANALOG OFF
    TOUCH_XM = 0u;      //    digitalWrite(_xm, LOW);
    bFM4_GPIO_ADE_AN07 = 1u;   // ANALOG 7 ON
     
    //getAnalogValues(&analog0, &analog3, &analog4, &analog6, &analog7, &analog16,&analog17);
    /*
     *  DOUBLE SAMPLING
     */
  /*
    for (i=0; i<2; i++) {
        samples[i] = analogRead(_xm);
    }

    if (samples[0] - samples[1] < -4 || samples[0] - samples[1] > 4) {
        valid = 0;
    } else {
        samples[1] = (samples[0] + samples[1]) >> 1; // average 2 samples
    }
    
    return (1023-samples[1]);
    */
}

/**
 *  Read preassure Z
 */
unsigned int NOTUSEDreadTouchZ() {
    /*
    // The resistance between X+ and X-
    int _rxplate = 300;
    
    
    // Set X+ to ground
    TOUCH_XP_IO = 1u;   // pinMode(_xp, OUTPUT);
    TOUCH_XP = 0u;      // digitalWrite(_xp, LOW);
    
    // Set Y- to VCC
    TOUCH_YM_IO = 1u;   // pinMode(_ym, OUTPUT);
    TOUCH_YM = 1u;      // digitalWrite(_ym, HIGH);
    
    // Hi-Z X- and Y+
    TOUCH_XM = 0u;      // digitalWrite(_xm, LOW);
    TOUCH_XM_IO = 0u;   // pinMode(_xm, INPUT);
    TOUCH_YP = 0u;      // digitalWrite(_yp, LOW);
    TOUCH_YP_IO = 0u;   // pinMode(_yp, INPUT);
    
    int z1 = analogRead(_xm);
    int z2 = analogRead(_yp);
    
    if (_rxplate != 0) {
        // now read the x
        float rtouch;
        rtouch = z2;
        rtouch /= z1;
        rtouch -= 1;
        rtouch *= readTouchX();
        rtouch *= _rxplate;
        rtouch /= 1024;
        
        return rtouch;
    } else {
        return (1023-(z2-z1));
    }
    */
}


uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max){
  uint32_t result =  (x - in_min); // * (out_max - out_min) / (in_max - in_min) + out_min;
  result *= (out_max - out_min);
  result /= (in_max - in_min); 
  result += out_min;
  return result; 
}



/**
 *  Testbench for checking the right wiring of the pins.    
 *  For the IO HIGH means OUTPUT and LOW means INPUT.
 *  @author Puria Izady
 */
void testbench(){
    // TESTBENCH
    LCD_D0_IO  = 1u; // Direction: Output
    LCD_D1_IO  = 1u; // Direction: Output
    LCD_D2_IO  = 1u; // Direction: Output
    LCD_D3_IO  = 1u; // Direction: Output
    LCD_D4_IO  = 1u; // Direction: Output
    LCD_D5_IO  = 1u; // Direction: Output
    LCD_D6_IO  = 1u; // Direction: Output
    LCD_D7_IO  = 1u; // Direction: Output
    
    // SET ANALOG PINS TO DIGITAL
    bFM4_GPIO_ADE_AN00 = 1;  // J2 Y ANALOG ON
    bFM4_GPIO_ADE_AN01 = 0;
    // bFM4_GPIO_ADE_AN02 = 0;
    bFM4_GPIO_ADE_AN03 = 1;  // J2 X ANALOG ON
    bFM4_GPIO_ADE_AN04 = 1;  // J1 Y ANALOG ON
    bFM4_GPIO_ADE_AN16 = 1;  // J1 X ANALOG ON
    bFM4_GPIO_ADE_AN11 = 0;  // D0/P1B ANALOG OFF
    bFM4_GPIO_ADE_AN12 = 0;  // D1/P1C ANALOG OFF
    bFM4_GPIO_ADE_AN06 = 1;  // LCD_TOUCH Xm ANALOG ON
    bFM4_GPIO_ADE_AN07 = 1;  // LCD_TOUCH Yp ANALOG ON
    
    // SET LCD SPI PINS TO OUTPUT MODE
    LCD_RD_IO = 1u;
    LCD_WR_IO = 1u;
    LCD_CD_IO = 1u;
    LCD_CS_IO = 1u;
    LCD_RS_IO = 1u;
    

    LCD_D7 = 0u;
    LCD_D6 = 0u;
    LCD_D5 = 0u;
    LCD_D4 = 0u;
    LCD_D3 = 0u;
    LCD_D2 = 0u;
    LCD_D1 = 1u;
    LCD_D0 = 1u;
    
    LCD_CS = 0u;
    LCD_CD = 0u;
    LCD_WR = 0u; 
    LCD_RD = 1u; 
    LCD_RS = 0u;   
}


void writeHello() {
    int cursor_x = 20;
    int cursor_y = 150;
    char myText[] = "Hallo das ist ein ganz schoen langer test aber muss sein digger. Lorem Impsum still Rocks!";
    int i = 0;
    for(i = 0; i< sizeof(myText)/sizeof(myText[0]); i++){
      write(myText[i], &cursor_x, &cursor_y, 1, BLACK, GREEN);
    } 
}

/**
 * Prints a Love-Text with a red background. Still buggy the whole text isn't printed.
 */
void printLove(char myText[]){
    int cursor_x = 20;
    int cursor_y = 150;
    int size = sizeof(myText)/sizeof(myText[0]);
    int i = 0;
    for(i = 0; i< size; i++){
      write(myText[i], &cursor_x, &cursor_y, 4, BLACK, RED);
    }
    char buffer[20];
    itoa(size, buffer, 10);
    for(i = 0; i < 20; i++){
      write(buffer[i], &cursor_x, &cursor_y, 4, BLACK, RED);
    }
}


