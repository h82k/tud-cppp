#include "lcd.h"
#include "display.h"
//#include "analog.h"
//#include "blink.h"
//#include "blinkrainbow.h"
//#include "button.h"
//#include "joystick.h"

void main(){
  init();
  reset();
  setupLCD();
  //InitAdc();
  //initCursor();
  
  //printPattern(color565(0x00, 0xEA, 0xFF));
  //fillRect(10, 10, 4, 4, color565(0x00, 0xEA, 0xFF));
  drawPixel(20, 20, BLACK);
  //BlinkRainbowMain();
  //controllLEDsInit();
  //paintTouch();
  //newLEDinit();
  //while(1){
    //printValues();
    //controllLEDs();
  //}
}