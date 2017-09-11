#include "blink.h"

#include <stdint.h>
#include "delay.h"
#include "s6e2ccxj.h"

int BlinkMain() {
  LED_BLUE_DDR |= (1 << LED_BLUE_PIN); // Configure blue LED pin as output.
  LED_BLUE_DOR |= (1 << LED_BLUE_PIN); // Turn LED off.
  
  const uint32_t sleepTime = 1000000;

  // Main loop
  while (1) {
    // Clear 8th bit -> Switch LED on
    LED_BLUE_DOR &= ~(1 << LED_BLUE_PIN);
    microDelay(sleepTime); 
		
    // Set 8th bit -> Switch LED off
    LED_BLUE_DOR |= (1 << LED_BLUE_PIN);
    microDelay(sleepTime);
  }
}

