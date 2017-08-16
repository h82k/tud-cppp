#include "touch.h"

void debugTouch(){
    // Write headline on the display
    setCursor(480,320);
    char freeSpace[] = " ";
    char headlineText[] = "      DEBUG TOUCHSCREEN";
    writeTextln(freeSpace);
    writeTextln(freeSpace);
    writeTextln(freeSpace);
    writeTextln(headlineText);
    writeTextln(freeSpace);
    
    // Get analog values of the touchscreen
    uint16_t touchX, touchY, touchZ;
    touchX = readTouchX();
    touchY = readTouchY();
    touchZ = readTouchZ();
    
    // Write x,y, and z-values on the screen
    char touchXText[] = "      Touch X: ";
    char touchYText[] = "      Touch Y: ";
    char touchZText[] = "      Touch Z: ";
    writeText(touchXText);
    write3Digits16Bit(&touchX);
    writeText(touchYText);
    write3Digits16Bit(&touchY);
    writeText(touchZText);
    write3Digits16Bit(&touchZ);
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
    touchPoint.x = readTouchX();
    touchPoint.y = readTouchY();
    touchPoint.z = readTouchZ();
    
    
    
    if (touchPoint.z > TOUCHZMIN && touchPoint.z < TOUCHZMAX) {
        // earase
        if (touchPoint.y < BOXSIZE && touchPoint.x > BOXSIZE*7) {
            fillRect(0, BOXSIZE, 480, 320-BOXSIZE, BLACK);
        }
        
        // change color
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
        
        // draw a point on the screen
        if (((touchPoint.y-PENRADIUS) > BOXSIZE) && ((touchPoint.y+PENRADIUS) < 480)) {
            fillCircle(touchPoint.x, touchPoint.y, PENRADIUS, currentcolor);
        }
    }
}

void paintTouch(){
    initPaintTouch();
    while(1){
        loopPaintTouch();
    }
}
