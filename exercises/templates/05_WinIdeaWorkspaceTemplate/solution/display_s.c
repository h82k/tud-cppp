#include "display_s.h"

#include <stdint.h>
#include "s6e2ccxj.h"
#include "gfx.h"
#include "glcdfont.h"


uint16_t color565_s(uint8_t r, uint8_t g, uint8_t b){
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void printPattern_s(){
  uint16_t x,y;
  for(x=0; x<480;x=x+8){
    for(y=0;y<320;y=y+8){
      fillRect(x,y,4,4,WHITE);
    }
  }
}

void initCursor_s(){
    cursorX = 0;
    cursorY = 0;
    textColor = WHITE;
    textSize = 2;
    textBackground = BLACK;
}

void setCursor_s(int16_t x, int16_t y) {
    cursorX = x;
    cursorY = y;
}

void setTextColor_s(uint16_t c) {
    // For 'transparent' background, we'll set the bg to the same as the rest of the display
    textColor = c;
}

void setTextSize_s(uint8_t s) {
    textSize = (s > 0) ? s : 1;
}

void setBackgroundColor_s(int bg){
    textBackground = bg;
}

void drawChar_s(int x, int y,  char c,  int color,  int bg, char size) {
    if((x >= 480)            || // Clip right
       (y >= 320)           || // Clip bottom
       ((x + 6 * size - 1) < 0) || // Clip left
       ((y + 8 * size - 1) < 0))   // Clip top
        return;

    char i, j;
    for(i=0; i<6; i++ ) {  // draw in x-direction
        char line;
        if(i < 5) line = font[(c*5)+i];  // save the i.x-line from (i,j) to (i,j+7) in the char line
        else      line = 0x0;
        for(j=0; j<8; j++, line >>= 1) {  // draw in y-direction
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

void writeAuto_s(char c) {
    if(c == '\n') {
        cursorY -= textSize*8;
        cursorX  = 0;
    } else if(c == '\r') {

    } else {
        if(((cursorX + textSize * 6) >= 480)) { // Heading off edge
            cursorX  = 0;            // Reset x to zero
            cursorY -= textSize * 8; // Advance y one line
        }
        if(((cursorY - textSize * 6) <= 0)) { // Heading off edge
            cursorY  = 319;            // Advance y one line
            cursorX  = 0;              // Reset x to zero
        }
        
        drawChar_s(cursorX ,cursorY , c, textColor, textBackground, textSize);
        cursorX += textSize * 6;
    }
}

void writeText_s(char *text){
    int i;
    for(i = 0; text[i] != 0; i++){
        writeAuto_s(text[i]);
    }
}

void writeTextln_s(char *text){
    int i;
    for(i = 0; text[i] != 0; i++){
        writeAuto_s(text[i]);
    }
    cursorY -= textSize*8;
    cursorX  = 0;
}

void writeNumberOnDisplay_s(uint16_t *value){
    char buffer[20];
    itoa(*value, buffer, 10);
    writeText_s(buffer);
}
