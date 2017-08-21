#include "blinkrainbow.h"

#include <stdint.h>
#include "delay.h"
#include "s6e2ccxj.h"
#include "mcu.h"


int BlinkRainbowMain() {
  // Declare pointers for the red, green and blue LED
  
	
  // Turn analog off for red led and initialize direction and value
  
  // Turn analog off for green led and initialize direction and value
  
  // Turn analog off for blue led and initialize direction and value
  
	
	// Main loop. Color order: red, green, blue
	while (1) {
    
		// Set Port 1 Pin 8 -> Switch blue LED off

    // Clear Port 1 Pin 10 -> Switch red LED on
    
    // delay 
    
    // Set Port 1 Pin 10 -> Switch red LED off

    // Clear Port B Pin 2 -> Switch green LED off

    
    // delay 
    
    // Set Port B Pin 2 -> Switch green LED off

		// Clear Port 1 Pin 8 -> Switch blue LED on

    
    // delay
    
  }
}

