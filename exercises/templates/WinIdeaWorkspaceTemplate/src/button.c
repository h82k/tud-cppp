#include "button.h"

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

/**
 * Returns true (1) if the button is pressed
 */
static int isButtonPressed() {
  // Return 1 if button is pressed, 0 otherwise.
  return -1;
}

/**
 *  Changes the status of the blue LED.
 */
static void toggleBlueLED(){
  // invert value of LEDStatus
}

/**
 *  Sets the blue LED to its status.
 */
static void setBlueLED(uint8_t status){
  // Set value register of blue LED to ledStatus
}
            