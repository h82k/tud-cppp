#include "display.h"

#include <stdint.h>
#include "s6e2ccxj.h"
#include "gfx.h"
#include "glcdfont.h"


uint16_t color565(uint8_t r, uint8_t g, uint8_t b){
  const uint8_t hiR = (r & 0xF8) >> 3; 
  const uint8_t hiG = (g & 0xFC) >> 2;
  const uint8_t hiB = (b & 0xF8) >> 3;
  const uint16_t result = (hiR << 11) | (hiG << 5) | hiB;
  return result;
  // A more compact solution is:
  // return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void printPattern(){
    // missing
}

void initCursor(){
    cursorX = 0;
    cursorY = 0;
    textColor = WHITE;
    textSize = 2;
    textBackground = BLACK;
}

void setCursor(int16_t x, int16_t y) {
    cursorX = x;
    cursorY = y;
}

void setTextColor(uint16_t c) {
    // For 'transparent' background, we'll set the bg to the same as the rest of the display
    textColor = c;
}

void setTextSize(uint8_t s) {
    textSize = (s > 0) ? s : 1;
}

void setBackgroundColor(int bg){
    textBackground = bg;
}

void drawChar(int x, int y,  char c,  int color,  int bg, char size) {
    if((x >= 480)            || // Clip right
       (y >= 320)           || // Clip bottom
       ((x + 6 * size - 1) < 0) || // Clip left
       ((y + 8 * size - 1) < 0))   // Clip top
        return;

    char i, j;
    for(i=0; i<6; i++ ) {  // draw in x-direction
        char line;
        if(i < 5) line = font[(c*5)+i];  // check if the char has a pixel at (i,j)
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

void writeAuto(char c) {
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
            cursorY  = 319;            // Reset x to zero
            cursorX  = 0; // Advance y one line
        }
        
        drawChar(cursorX ,cursorY , c, textColor, textBackground, textSize);
        cursorX += textSize * 6;
    }
}

void writeText(char *text){
    int i;
    for(i = 0; text[i] != 0; i++){
        writeAuto(text[i]);
    }
}

void writeTextln(char *text){
    int i;
    for(i = 0; text[i] != 0; i++){
        writeAuto(text[i]);
    }
    cursorY -= textSize*8;
    cursorX  = 0;
}

void writeNumberOnDisplay(uint16_t *value){
    char buffer[20];
    itoa(*value, buffer, 10);
    writeText(buffer);
}
