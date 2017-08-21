#include "button.h"

static volatile uint32_t *blueLEDDirectionPort;
static volatile uint32_t *blueLedValuePort;
static uint8_t ledStatus;

void ButtonToggleBlueLED(){
   // initialization
   
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

static void initLed(){
  // set LED status
  
  // initialize PF5 as input and activate pullup resistor
  
  // initialize blue LED
}

static void toggleBlueLED(){
  // invert value of ledStatus

}

static void setBlueLed(uint8_t status){
  // Set value register of blue led to ledStatus
}
                  
