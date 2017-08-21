#include "src/button.h"

#include "pdl_header.h"
#include "s6e2ccxj.h"

static volatile uint32_t *blueLedValuePort;
static uint8_t ledStatus;

void ButtonToggleBlueLED_s(){
  initLed();
  const uint32_t sleepTime = 100000;
   
  while(1){
    if(isButtonPressed()){
      toggleBlueLED();
      while(isButtonPressed());
    }
    setBlueLed(ledStatus);
    microDelay(sleepTime);
  }  
}
                          
void ButtonHoldBlueLEDOn_s() {
  initLed();
  const uint32_t sleepTime = 100000;
  while(1){
    
    while(isButtonPressed()){
      setBlueLed(1u); 
      microDelay(sleepTime);
    }
    
    setBlueLed(0u);
    microDelay(sleepTime);
    
  }
}

static int isButtonPressed() {
  // Inverted logic as input is pulled up
  return Gpio1pin_Get(GPIO1PIN_PF5) == 0;                             
}

static void initLed(){
  ledStatus = 0u;
  Gpio1pin_InitIn(GPIO1PIN_PF5, Gpio1pin_InitPullup(1u)); // initialize PF5 as input and activate pullup resistor
  
  volatile uint32_t *blueLEDDirectionPort = &(FM4_GPIO->DDR1);
  blueLedValuePort = &(FM4_GPIO->PDOR1);
  
	bFM4_GPIO_ADE_AN08 = 0; // Disable analog-digital channel 08
  *blueLEDDirectionPort |= 0x0100; // Configure Port 1 Pin 8 as output pin
  *blueLedValuePort |= 0x0100; // Switch LED off
}

static void toggleBlueLED(){
  if(ledStatus)
    ledStatus = 0u;
  else
    ledStatus = 1u;
}

static void setBlueLed(uint8_t status){
  if(status)
    *blueLedValuePort &= 0xFEFF; 
  else
    *blueLedValuePort |= 0x0100; 
}
                  
