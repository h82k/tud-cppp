
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "gfx.h"
#include "analog.h"
#include "tftpaint.h"
#include "pong.h"
#include "DHT11.h"
#include "debug.h"

void main(){
    init();
    reset();
    setupLCD();
    initCursor();
    InitAdc();
    fillScreen(BLACK);
    //testGraphics();
    //initTFTPaint();
    //pong_init();
    while(1){
      getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);
      //loopTFTPaint();
      //pong_loop();
      //rauminformationen();
      debugPeripherie();
    }
}