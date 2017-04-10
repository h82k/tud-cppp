#define BOXSIZE 40
#define PENRADIUS 3

/***
 *    GLOBAL VARIABLES
 ****/
uint16_t oldcolor, currentcolor;

void initTFTPaint(){
    
  fillScreen(BLACK);
  fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
  fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
  fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
  fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
  fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
  // tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, WHITE);
 
  drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
  currentcolor = RED;
  
  setCursor(260, 25);
  setTextSize(2);
  char text[] = "BILD ERNEUERN";
  writeText(text);
 
}

void loopTFTPaint()
{
  touchPoint.x = readTouchX();
  touchPoint.y = readTouchY();
  touchPoint.z = readTouchZ();



  if (touchPoint.z > TOUCHZMIN && touchPoint.z < TOUCHZMAX) {
    //printTouchValues();
    
    
    if (touchPoint.y < (TOUCHYMIN-5)) {
      // earase
      // press the bottom of the screen to erase 
      fillRect(0, BOXSIZE, 480, 320-BOXSIZE, BLACK);
    }

    if (touchPoint.y < BOXSIZE) {
       oldcolor = currentcolor;

       if (touchPoint.x < BOXSIZE) { 
         currentcolor = RED; 
         drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
       } else if (touchPoint.x < BOXSIZE*2) {
         currentcolor = YELLOW;
         drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
       } else if (touchPoint.x < BOXSIZE*3) {
         currentcolor = GREEN;
         drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, WHITE);
       } else if (touchPoint.x < BOXSIZE*4) {
         currentcolor = CYAN;
         drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, WHITE);
       } else if (touchPoint.x < BOXSIZE*5) {
         currentcolor = BLUE;
         drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, WHITE);
       } else if (touchPoint.x < BOXSIZE*6) {
         currentcolor = MAGENTA;
         drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, WHITE);
       }

       if (oldcolor != currentcolor) {
          if (oldcolor == RED) fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
          if (oldcolor == YELLOW) fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
          if (oldcolor == GREEN) fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
          if (oldcolor == CYAN) fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
          if (oldcolor == BLUE) fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
          if (oldcolor == MAGENTA) fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
       }
    }
    if (((touchPoint.y-PENRADIUS) > BOXSIZE) && ((touchPoint.y+PENRADIUS) < 480)) {
      fillCircle(touchPoint.x, touchPoint.y, PENRADIUS, currentcolor);
    }
  }
}

