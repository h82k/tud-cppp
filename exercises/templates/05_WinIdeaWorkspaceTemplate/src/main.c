#include "init.h"
#include "lcd.h"

int main(){
  initBoard();
  
  fillScreen(BLUE);
  drawChar_s(100, 100, 'Ä', YELLOW, RED, 10); 
  
  // #include "blinkrainbox_s.h"
  //BlinkRainbowMain_s();
  
  // #include "button_s.h"
  //ButtonToggleBlueLED_s();
  //ButtonHoldBlueLEDOn_s();
  
  // #include "graphicstest.h"
  //testGraphics();
  //testText();
  //testRotateText(); 
}