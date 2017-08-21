#include "button_s.h"

volatile uint32_t *blueLEDDirectionPort;
volatile uint32_t *blueLEDValuePort;
uint8_t LEDstatus;

void initLED_s(){
  LEDstatus = 0u;
  Gpio1pin_InitIn(GPIO1PIN_PF5, Gpio1pin_InitPullup(1u)); // initialize PF5 as input and activate pullup resistor
  
  blueLEDDirectionPort = &(FM4_GPIO->DDR1);
  blueLEDValuePort = &(FM4_GPIO->PDOR1);
  
	bFM4_GPIO_ADE_AN08 = 0; // Disable analog-digital channel 08
  *blueLEDDirectionPort |= 0x0100; // Configure Port 1 Pin 8 as output pin
  *blueLEDValuePort |= 0x0100; // Switch LED off
}

void toggleBlueLED_s(){
  if(LEDstatus)
    LEDstatus = 0u;
  else
    LEDstatus = 1u;
}

void setBlueLED_s(uint8_t status){
  if(status)
    *blueLEDValuePort &= 0xFEFF; 
  else
    *blueLEDValuePort |= 0x0100; 
}
                  
int ButtonToggleBlueLED_s(){
   initLED_s();
   
   while(1){
    if(Gpio1pin_Get(GPIO1PIN_PF5) == 0){ // if JS1 button pressed
      toggleBlueLED_s();
      while(Gpio1pin_Get(GPIO1PIN_PF5) == 0); // waits until the button is pressed
    }
    setBlueLED_s(LEDstatus);
   }
          
}
                          
void ButtonHoldBlueLEDOn_s() {
  initLED_s();
  uint32_t sleepTime = 100000;
  while(1){
    while(Gpio1pin_Get(GPIO1PIN_PF5) == 0){ // Inverted logic as input is pulled up
      // Clear 8th bit -> Switch LED on
      setBlueLED_s(1u); 
      microDelay(sleepTime);
    }
    // Set 8th bit -> Switch LED off
    setBlueLED_s(0u);
    microDelay(sleepTime);
  }
}