#include "touch.h"

void debugTouch(){
    // get analog values
  
    // set cursor to (480,320)
  
    // Write headline on the display with 1 linebreak before and 4 afterwards
    
    // Get analog values of the touchscreen by using the readTouch methods
    
    // Write x,y, and z-values on the screen
   
}

void initPaintTouch(){
    fillScreen(BLACK);
    fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
    fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
    fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
    fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
    fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
    fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
    
    drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
    currentcolor = RED;
    
    setCursor(260, 25);
    setTextSize(2);
    char text[] = "BILD ERNEUERN";
    writeText(text);
}

void loopPaintTouch(){
    // save the actual touchpoint in the struct touchpoint
    
    
    // correct touchpoint
    if (touchPoint.z > TOUCHZMIN && touchPoint.z < TOUCHZMAX) {
        // earase
       
        
        // change color
        
        
        // draw a point on the screen

    }
}

void paintTouch(){
    // your code here ...
  
    while(1){
        getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);
        // your code here ...
    }
}
