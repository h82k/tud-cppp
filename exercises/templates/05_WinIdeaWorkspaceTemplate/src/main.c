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
  fillScreen(color565(0x00, 0xEA, 0xFF));
  //BlinkRainbowMain();
  //controllLEDsInit();
  //paintTouch();
  //newLEDinit();
  while(1){
    //printValues();
    //controllLEDs();
  }
}