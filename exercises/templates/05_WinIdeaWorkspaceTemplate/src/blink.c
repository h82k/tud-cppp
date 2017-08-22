#include "blink.h"

#include <stdint.h>
#include "delay.h"
#include "s6e2ccxj.h"

int BlinkMain() {
  volatile uint32_t *blueLEDDirectionPort = &(FM4_GPIO->DDR1);
  volatile uint32_t *blueLedValuePort = &(FM4_GPIO->PDOR1);
  
	bFM4_GPIO_ADE_AN08 = 0; // Disable analog-digital channel 08
  *blueLEDDirectionPort |= 0x0100; // Configure Port 1 Pin 8 as output pin
  *blueLedValuePort |= 0x0100; // Switch LED off
  
	const uint32_t sleepTime = 1000000;
	// Main loop
	while (1) {
		// Clear 8th bit -> Switch LED on
    *blueLedValuePort &= 0xFEFF; 
    microDelay(sleepTime); 
		
		// Set 8th bit -> Switch LED off
    *blueLedValuePort |= 0x0100;
    microDelay(sleepTime);
		
  }
}

