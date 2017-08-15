
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "gfx.h"
#include "analog.h"
#include "tftpaint.h"
#include "pong.h"
#include "DHT11.h"
#include "IntegrityCheck.h"

void initBlink() {           

  bFM4_GPIO_ADE_AN08 = 0; 
  
  // Blue
  FM4_GPIO->PDOR1_f.P8 = 1u; 
  FM4_GPIO->DDR1_f.P8 = 1u;
  
  // Green
  FM4_GPIO->PDORB_f.P2 = 1u; 
  FM4_GPIO->DDRB_f.P2 = 1u;
  
  // Red
  FM4_GPIO->PDOR1_f.PA = 1u; 
  FM4_GPIO->DDR1_f.PA = 1u;
}

void doBlink() {             
    volatile uint32_t u32Delay; 
    FM4_GPIO->PDOR1_f.P8 = 0u;
    for (u32Delay = 0u; u32Delay < 8000000ul; u32Delay++); 
    
    FM4_GPIO->PDOR1_f.P8 = 1u; // P18 output: high (LED off) 
    
    for (u32Delay = 0u; u32Delay < 8000000ul; u32Delay++);  
}

void main(){
    init();
    reset();
    setupLCD();
    initCursor();
    InitAdc();
    fillScreen(BLACK);
    initBlink();
    //testGraphics();
    //initTFTPaint();
    //pong_init();
    while(1){
      getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);
      //loopTFTPaint();
      //pong_loop();
      //rauminformationen();
      debugPeripherie(); 
      //doBlink();
    }
}