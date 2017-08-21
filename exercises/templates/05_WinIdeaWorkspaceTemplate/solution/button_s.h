#include <stdint.h>
#include "pdl_header.h"
#include "s6e2ccxj.h"

volatile uint32_t *blueLEDDirectionPort;
volatile uint32_t *blueLEDValuePort;
uint8_t LEDstatus;

/**
 *  Initializes the blue LED.
 */ 
void initLED_s();

/**
 *  Changes the status of the blue LED.
 */
void toggleBlueLED_s();

/**
 *  Sets the blue LED to its status.
 */
void setBlueLED_s(uint8_t status);

/**
 * Pressing the Joystick 1 Button toggles the LED, just like a light switch.
 */
int ButtonToggleBlueLED_s();

/**
 * Holding the Joystick 1 Button turns the LED on and leaving it turns the LED off.
 */
void ButtonHoldBlueLEDOn_s();