#include "display.h"

#include "gfx.h"
#include "glcdfont.h"


static int16_t cursorX, cursorY;
static uint16_t textColor;
static uint8_t textSize;
static int textBackground;

uint16_t color565(uint8_t r, uint8_t g, uint8_t b){
    // your code here... 
}

void printPattern(uint16_t backgroundColor, uint16_t foregroundColor) {
  // your code here...
}

void initCursor(){
  // your code here...
  
}

void setCursor(int16_t x, int16_t y) {
  // your code here...
}

void setTextColor(uint16_t c) {
  // For 'transparent' background, we'll set the bg to the same as the rest of the display
  // your code here...
}

void setTextSize(uint8_t s) {
  // your code here...
}

void setBackgroundColor(int bg){
  // your code here...
}

void drawChar(int x, int y,  char c,  int color,  int bg, char size) {
    // if (x,y) is not inside the display return

    char i, j;
    for(i=0; i<6; i++ ) {  // draw in x-direction
        char line; // line (i,j) ... (i,j+7)
        // save the i.x-line from (i,j) to (i,j+7) in the char line
        
        for(j=0; j<8; j++, line >>= 1) {  // draw in y-direction
            
        }
    }
}

void writeAuto(char c) {
  // if char c == '\n' then jump cursor to next line
  
  // else
  // check for end of line and reset cursor. in the case of end of the display set cursorY to the starting point.
  // draw the char
  // move cursorX
}

void writeText(char *text){
    // your code here ... 
}

void writeTextln(char *text){
    // your code here ... 
}

void writeNumberOnDisplay(uint16_t *value){
    // your code here...
}
