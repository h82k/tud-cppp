/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "pdl_header.h"
#include "lcd.h"
#include "analog.h"
#include <stdio.h>
#include <stdlib.h>
#include "graphicstest.h"
#include "pong.h"
#include "tftpaint.h"

       

/**
 *    Analog Messungen und Anzeige der Waerte auf dem Display.
 */
void analyseAnalogDevices(){
    analogPolling();
    // TEST - set LED color based on ADC value
    ChangeLED();
    old = u8Data;
}

void standardDelay(){
    uint32_t u32Delay;
    // delay
    for(u32Delay = 0; u32Delay<100000;u32Delay++);
}

void printBrightnessOnLCD(){
      char brightnessText[] = "Die Helligkeit betraegt: ";
      setCursor(480,320);
      fillScreen(BLACK);
      writeText(brightnessText);
      write8BitValueOnLCD(&analog17);
}

void printJS1OnLCD(){
      char JS1XText[] = "Die X-Ordinate von JS1: ";
      char JS1YText[] = "Die Y-Ordinate von JS1: ";
      setCursor(480,320);
      fillScreen(BLACK);
      writeText(JS1XText);
      write8BitValueOnLCD(&analog16);
      writeText(JS1YText);
      write8BitValueOnLCD(&analog4);
}

void printJS2OnLCD(){
      char JS2XText[] = "Die X-Ordinate von JS2: ";
      char JS2YText[] = "Die Y-Ordinate von JS2: ";
      setCursor(480,320);
      fillScreen(BLACK);
      writeText(JS2XText);
      write8BitValueOnLCD(&analog3);
      writeText(JS2YText);
      write8BitValueOnLCD(&analog0);
}

void printJS2OnLCDrasterized(){
      char JS2XText[] = "Die X-Ordinate von JS2: ";
      char JS2YText[] = "Die Y-Ordinate von JS2: ";
      setCursor(480,320);
      fillScreen(BLACK);
      float32_t analog0fixed = analog0*1.25;
      float32_t analog3fixed = analog3*1.25;
      uint16_t analog0value = (uint16_t)analog0fixed;
      uint16_t analog3value = (uint16_t)analog3fixed;
      writeText(JS2XText);
      write16BitValueOnLCD(&analog3value);
      writeText(JS2YText);
      write16BitValueOnLCD(&analog0value);
}

void pointGame(uint8_t chooseJoystick){
    // Choose which controller
    /*
    switch(chooseJoystick){
    case 1: break;
    case 2: break;
    }
    */
  
    // draw WHITE Point in the middle of the Screen
    fillCircle(240, 160, 10, MAGENTA);
    
    while(1){
      getAnalogValues(&analog0, &analog3, &analog4, &analog6, &analog7, &analog16,&analog17);
    //JS2 OBEN UNTEN ueber ANALOG3
     if(analog3<185){
          fillCircle(240, 160, 10, BLACK);
          fillCircle(240, 300, 10, MAGENTA);
      }
    }
    
}

void printTouchY() {
  /* WRONG VERSION 
    TOUCH_YP_IO = 0u;   //    pinMode(_yp, INPUT);
    TOUCH_YM_IO = 0u;   //    pinMode(_ym, INPUT);
    TOUCH_YP = 0u;      //    digitalWrite(_yp, LOW);
    TOUCH_YM = 0u;      //    digitalWrite(_ym, LOW);

    TOUCH_XP_IO = 1u;   //    pinMode(_xp, OUTPUT);
    TOUCH_XP = 1u;      //    digitalWrite(_xp, HIGH);
    TOUCH_XM_IO = 1u;   //    pinMode(_xm, OUTPUT);
    TOUCH_XM = 0u;      //    digitalWrite(_xm, LOW);
    
  */
    TOUCH_YP_IO = 1u;   //    pinMode(_yp, OUTPUT);
    TOUCH_YM_IO = 1u;   //    pinMode(_ym, OUTPUT);
    bFM4_GPIO_ADE_AN07 = 0u;  // ANALOG 7 OFF
    TOUCH_YP = 0u;      //    digitalWrite(_yp, LOW);
    TOUCH_YM = 0u;      //    digitalWrite(_ym, LOW);
    TOUCH_YP_IO = 0u;   //    pinMode(_yp, INPUT);
    TOUCH_YM_IO = 0u;   //    pinMode(_ym, INPUT);

    TOUCH_XP_IO = 1u;   //    pinMode(_xp, OUTPUT);
    TOUCH_XP = 1u;      //    digitalWrite(_xp, HIGH);
    TOUCH_XM_IO = 1u;   //    pinMode(_xm, OUTPUT);
    bFM4_GPIO_ADE_AN06 = 0u; // Xm/P16 ANALOG OFF
    TOUCH_XM = 0u;      //    digitalWrite(_xm, LOW);
    bFM4_GPIO_ADE_AN07 = 1u;   // ANALOG 7 ON
     
    getAnalogValues(&analog0, &analog3, &analog4, &analog6, &analog7, &analog16,&analog17);
    //setCursor(480,320);
    //fillScreen(BLACK);
    char text[] = "Die Y-Koordinate ist: ";
    writeText(text);
    write8BitValueOnLCD(&analog7);
}

void printTouchX(){
    TOUCH_XP_IO = 1u;   // pinMode(_xp, OUTPUT);
    TOUCH_XM_IO = 1u;   // pinMode(_xm, OUTPUT);
    bFM4_GPIO_ADE_AN06 = 0u; // ANALOG 6 OFF
    TOUCH_XP = 0u;      // digitalWrite(_xp, LOW);
    TOUCH_XM = 0u;      // digitalWrite(_xm, LOW);
    TOUCH_XP_IO = 0u;   // pinMode(_xp, INPUT);
    TOUCH_XM_IO = 0u;   // pinMode(_xm, INPUT);
    
    bFM4_GPIO_ADE_AN07 = 0u;   // ANALOG7 OFF
    TOUCH_YP_IO = 1u;   // pinMode(_yp, OUTPUT);
    TOUCH_YP = 1u;      // digitalWrite(_yp, HIGH);
    TOUCH_YM_IO = 1u;   // pinMode(_ym, OUTPUT);
    TOUCH_YM = 0u;      // digitalWrite(_ym, LOW);
    bFM4_GPIO_ADE_AN06 = 1u; // ANALOG 6 ON
    
    getAnalogValues(&analog0, &analog3, &analog4, &analog6, &analog7, &analog16,&analog17);
    setCursor(480,320);
    fillScreen(BLACK);
    char text[] = "Die X-Koordinate ist: ";
    writeText(text);
    write8BitValueOnLCD(&analog6);
}

void printTouchZ(){
    uint16_t rXPlate = 248;  // Resistance between X+ and X-
 
    // Set X+ to ground
    TOUCH_XP_IO = 1u;   // pinMode(_xp, OUTPUT);
    TOUCH_XP = 0u;      // digitalWrite(_xp, LOW);
    
    // Set Y- to VCC
    TOUCH_YM_IO = 1u;   // pinMode(_ym, OUTPUT);
    TOUCH_YM = 1u;      // digitalWrite(_ym, HIGH);
    
    // Hi-Z X- and Y+
    bFM4_GPIO_ADE_AN06 = 0u; //Xm/Analog 6 OFF
    bFM4_GPIO_ADE_AN07 = 0u; //Yp/Analog 7 OFF
    TOUCH_XM_IO = 1u; // Xm OUTPUT
    TOUCH_XM = 0u;      // digitalWrite(_xm, LOW);
    TOUCH_YP = 1u;      // Yp OUTPUT
    TOUCH_YP = 0u;      // digitalWrite(_yp, LOW);
    
    TOUCH_XM_IO = 0u;   // pinMode(_xm, INPUT);
    TOUCH_YP_IO = 0u;   // pinMode(_yp, INPUT);
    bFM4_GPIO_ADE_AN06 = 1u; //Xm/Analog 6 ON
    bFM4_GPIO_ADE_AN07 = 1u; //Yp/Analog 7 ON
    
    getAnalogValues(&analog0, &analog3, &analog4, &analog6, &analog7, &analog16,&analog17);
    uint8_t z1 = analog6; // z1 = Xm = analog6
    uint8_t z2 = analog7; // z2 = Ym = analog7
    
    /*
    if(rXPlate != 0){
        float rtouch;
        rtouch = z2;
        rtouch /= z1;
        rtouch -= 1;
        rtouch *= readTouchX();
        rtouch *= _rxplate;
        rtouch /= 1024;
    }
    else{
    */
      uint8_t result = 255-(z2-z1);
    //}
    char text[] = "Der Touch-Druck ist: ";
    writeText(text);
    write8BitValueOnLCD(&result); 
}



/**
 ******************************************************************************
 ** \brief  Main function
 **
 ** \return int32_t return value, if needed
 ******************************************************************************/
int32_t main( void )
{
    
    InitAdc(17);          // initialize ADC
    InitMfs();          // initialize MFS
    InitLED();          // initialize GPIO for RGB-LED
    
    SendStringMfs("\fADC Digital Voltage Meter - using Light-Senosr (AN17)");
    
    /**
      * LCD PART
      */
    //testbench();
    
    
    init();
    reset();
    setupLCD();
    fillScreen(BLACK);
    setCursor(480,320);
    setTextSize(2);
    //pong_init();
    //testGraphics();
    initTFTPaint();


    while (1)
    {
      //analyseAnalogDevices(); 
      //getAnalogValues(&analog0, &analog3, &analog4, &analog6, &analog7, &analog16,&analog17);
      //printBrightnessOnLCD();
      //printJS2OnLCD();
      //pointGame(0);
      
      //printBrightnessOnLCD();
      //printJS2OnLCDrasterized();
      //pong_loop();
      
      /*
      printTouchX();
      printTouchY();
      printTouchZ();
      */
      //printTouchValues();
      loopTFTPaint();
      
  
      
      
    }  // while(1)
    
}  // main()

/*****************************************************************************/
/* EOF (not truncated)                                                       */
/*****************************************************************************/
