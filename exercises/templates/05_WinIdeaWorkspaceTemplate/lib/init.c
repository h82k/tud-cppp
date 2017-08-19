#include "init.h"

void initBoard(){
  init();
  reset();
  setupLCD();
  initCursor();
  InitAdc();
  fillScreen(BLACK);
  setCursor(480,320);
}