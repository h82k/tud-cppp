#include "button.h"

static volatile uint32_t *blueLEDDirectionPort;
static volatile uint32_t *blueLedValuePort;
static uint8_t ledStatus;

static void initLED(){
  // set LED status
  
  // initialize PF5 as input and activate pullup resistor
  
  // initialize blue Led
}

void ButtonToggleBlueLED(){
  // Initialization
  
  while(1){
    // if button pressed toggle ledStatus and wait unitl button is released
    // set LED
  }
  
}
                          
void ButtonHoldBlueLEDOn() {
  // initialization

  while(1){
    // while button pressed turn LED on
    // delay of 0,01s
    
    // normal case LED is off
    // delay of 0,01s
  }
}

static int isButtonPressed() {
  // Return 1 if button is pressed, 0 otherwise. 
}

static void toggleBlueLED(){
  // invert value of LEDStatus

}

static void setBlueLed(uint8_t status){
  // Set value register of blue LED to ledStatus
}
                  
