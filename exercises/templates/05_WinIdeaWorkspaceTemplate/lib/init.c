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
}