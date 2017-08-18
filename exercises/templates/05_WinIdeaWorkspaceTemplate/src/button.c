#include "button.h"

#include <stdint.h>
#include "s6e2ccxj.h"

#include "delay.h"

int ButtonMain() {
  volatile uint32_t* blueLEDValuePort = &(FM4_GPIO->PDOR1);
  volatile uint32_t* blueLEDDirectionPort = &(FM4_GPIO->DDR1);
  
	bFM4_GPIO_ADE_AN08 = 0; // Disable analog-digital channel 08
  *blueLEDValuePort |= 0x0100; // Switch LED off
  *blueLEDDirectionPort |= 0x0100; // Configure Port 1 Pin 9 as output pin
  
	const uint32_t sleepTime = 1000000;
	// Main loop
	while (1) {
		
		// Clear 9th bit -> Switch LED on
    *blueLEDValuePort &= 0xFEFF; 
    microDelay(sleepTime); 
		
		// Set 9th bit -> Switch LED off
    *blueLEDValuePort |= 0x0100;
    microDelay(sleepTime);
		
  }
}