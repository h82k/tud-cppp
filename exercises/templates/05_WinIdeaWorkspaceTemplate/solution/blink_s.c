#include "blink_s.h"

#include <stdint.h>
#include "delay.h"
#include "s6e2ccxj.h"

int BlinkMain() {
  volatile uint32_t *blueLEDDirectionPort = &(FM4_GPIO->DDR1);
  volatile uint32_t *blueLEDValuePort = &(FM4_GPIO->PDOR1);
  
	bFM4_GPIO_ADE_AN08 = 0; // Disable analog-digital channel 08
  *blueLEDDirectionPort |= 0x0100; // Configure Port 1 Pin 8 as output pin
  *blueLEDValuePort |= 0x0100; // Switch LED off
  
	const uint32_t sleepTime = 1000000;
	// Main loop
	while (1) {
		
		// Clear 8th bit -> Switch LED on
    *blueLEDValuePort &= 0xFEFF; 
    microDelay(sleepTime); 
		
		// Set 8th bit -> Switch LED off
    *blueLEDValuePort |= 0x0100;
    microDelay(sleepTime);
		
  }
}

