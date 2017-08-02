#include <stdint.h>
#include "delay.h"
#include "s6e2ccxj.h"

int BlinkMain() {
  const uint32_t sleepTime = 1000000;
  volatile uint32_t* blueLEDValuePort = &(FM4_GPIO->PDOR1);    // Port 1 values
  volatile uint32_t* blueLEDDirectionPort = &(FM4_GPIO->DDR1); // Port 1 I/O configurations
  bFM4_GPIO_ADE_AN08 = 0;                                      // Disable Analog 8
  *blueLEDValuePort |= 0x0100;
  *blueLEDDirectionPort |= 0x0100;
  while (1) {
    *blueLEDValuePort &= 0xFEFF; 
    microDelay(sleepTime); 
    *blueLEDValuePort |= 0x0100;
    microDelay(sleepTime);
  }
}

