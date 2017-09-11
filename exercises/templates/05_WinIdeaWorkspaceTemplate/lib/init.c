#include "init.h"
#include "lcd.h"
#include "src/display.h"

void initBoard(){
  init();
  reset();
  setupLCD();
  initCursor_s();
  InitAdc();
  fillScreen(BLACK);
  setCursor_s(480,320);

  bFM4_GPIO_ADE_AN08 = 0; // Disable analog-digital channel 08
  bFM4_GPIO_ADE_AN10 = 0; // Disable analog-digital channel 10
  bFM4_GPIO_ADE_AN18 = 0; // Disable analog-digital channel 18
}
