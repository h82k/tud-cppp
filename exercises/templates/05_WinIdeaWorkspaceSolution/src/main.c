#include "lcd.h"
#include "analog.h"
#include "blink.h"
#include "blinkrainbow.h"
#include "button.h"
#include "joystick.h"
#include "display.h"

void main(){
  init();
  reset();
  setupLCD();
  initCursor();
  InitAdc();
  fillScreen(BLACK);
  //BlinkRainbowMain();
  controllLEDsInit();
  //paintTouch();
  //newLEDinit();
  while(1){
    //printValues();
    controllLEDs();
  }
}