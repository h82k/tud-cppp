#include "blinkrainbow_s.h"

#include <stdint.h>
#include "delay.h"
#include "s6e2ccxj.h"
#include "mcu.h"


int BlinkRainbowMain_s() {
  volatile uint32_t *redLEDDirectionPort = &(FM4_GPIO->DDR1);
  volatile uint32_t *redLEDValuePort = &(FM4_GPIO->PDOR1);
  volatile uint32_t *greenLEDDirectionPort = &(FM4_GPIO->DDRB);
  volatile uint32_t *greenLEDValuePort = &(FM4_GPIO->PDORB);
  volatile uint32_t *blueLEDDirectionPort = &(FM4_GPIO->DDR1);
  volatile uint32_t *blueLedValuePort = &(FM4_GPIO->PDOR1);
  
	
  bFM4_GPIO_ADE_AN10 = 0; // Disable analog-digital channel 10
  *redLEDDirectionPort |= 0x0400; // Configure Port 1 Pin 10 as output pin
  *redLEDValuePort |= 0x0400; // Switch LED off
  
  bFM4_GPIO_ADE_AN18 = 0; // Disable analog-digital channel 18
  *greenLEDDirectionPort |= 0x0004; // Configure Port B Pin 2 as output pin
  *greenLEDValuePort |= 0x0004; // Switch LED off
  
  bFM4_GPIO_ADE_AN08 = 0; // Disable analog-digital channel 08
  *blueLEDDirectionPort |= 0x0100; // Configure Port 1 Pin 8 as output pin
  *blueLedValuePort |= 0x0100; // Switch LED off
  
	const uint32_t sleepTime = 1000000;
	// Main loop. Color order: red, green, blue
	while (1) {
    
		// Set Port 1 Pin 8 -> Switch blue LED off
    *blueLedValuePort |= 0x0100;
    // Clear Port 1 Pin 10 -> Switch red LED on
    *redLEDValuePort &= 0xFBFF;
    
    microDelay(sleepTime);
    
    // Set Port 1 Pin 10 -> Switch red LED off
    *redLEDValuePort |= 0x0400; // Switch LED off
    // Clear Port B Pin 2 -> Switch green LED off
    *greenLEDValuePort &= 0xFFFB;
    
    microDelay(sleepTime);
    
    // Set Port B Pin 2 -> Switch green LED off
    *greenLEDValuePort |= 0x0004;
		// Clear Port 1 Pin 8 -> Switch blue LED on
    *blueLedValuePort &= 0xFEFF; 
    
    microDelay(sleepTime); 
    
  }
}

