#include "button.h"

#include <stdint.h>
#include "pdl_header.h"
#include "s6e2ccxj.h"

int ButtonMain() {
  Gpio1pin_InitIn(GPIO1PIN_PF5, Gpio1pin_InitPullup(1u)); // initialize PF5 as input and activate pullup resistor
  uint32_t sleepTime = 100000;
  volatile uint32_t *blueLEDDirectionPort = &(FM4_GPIO->DDR1);
  volatile uint32_t *blueLEDValuePort = &(FM4_GPIO->PDOR1);
  
	bFM4_GPIO_ADE_AN08 = 0; // Disable analog-digital channel 08
  *blueLEDDirectionPort |= 0x0100; // Configure Port 1 Pin 8 as output pin
  *blueLEDValuePort |= 0x0100; // Switch LED off
  
  while(1){
    while(Gpio1pin_Get(GPIO1PIN_PF5) == 0){ // Inverted logic as input is pulled up
      // Clear 8th bit -> Switch LED on
      *blueLEDValuePort &= 0xFEFF; 
      microDelay(sleepTime);
    }
    // Set 8th bit -> Switch LED off
    *blueLEDValuePort |= 0x0100;
    microDelay(sleepTime);
  }
}