#include "init.h"
#include "lcd.h"

int main(){
  initBoard();
  
  // #include "blinkrainbox.h"
  //BlinkRainbowMain_s();
  
  // #include "button.h"
  //ButtonToggleBlueLED_s();
  //ButtonHoldBlueLEDOn_s();
  
  // #include "graphicstest.h"
  //testGraphics();
  //testText();
  //testRotateText(); 
  
  // #include "joystick.h"
  //controlLedsInit_s();
  while(1) {
    //controlLeds_s();
    printValues_s();
  }
  //printValues_s();
}
