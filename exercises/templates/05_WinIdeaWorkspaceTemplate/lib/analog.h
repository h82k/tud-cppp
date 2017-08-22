#ifndef ANALOG_H
#define ANALOG_H

#include "mcu.h"
#include "pdl_header.h"
#include "pins.h"

#define TOUCHXMIN   22 
#define TOUCHXMAX   220
#define TOUCHYMIN   50
#define TOUCHYMAX   192
#define TOUCHZMIN   5
#define TOUCHZMAX   185


/**
 * Initializes and starts A/D conversion for all relevant channels
 */
void InitAdc();

/**
 * Reads in raw data from A/D interface and stores the result in the given output parameter.
 */
void pollData(uint32_t *u32Data);

/**
 * Reads in all relevant analog channels (8 bit precision) and stores the results in the given output parameters.
 * The parameter names refer to the analog channel numbers.
 * For example, analog11 refers to channel AN11.
 */
void getAnalogValues(uint8_t *analog11, uint8_t *analog12, uint8_t *analog13, uint8_t *analog16, uint8_t *analog17,  uint8_t *analog19, uint8_t *analog23);

/**
 * Maps the given value 'x' (with min./max. possible values in_min/in_max) to the given output value range (out_min/out_max)
 */
uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);

/**
 * Reads the X-position of the currently detected touch point.
 * The return value is in the range of 0 to 480
 */
uint16_t readTouchX();

/**
 * Reads the Y-position of the currently detected touch point.
 * The return value is in the range of 0 to 320.
 */
uint16_t readTouchY();

/**
 * Reads the Z-position (=pressure) of the currently detected touch point.
 * The return value is in the range of 0 to 255.
 */
uint16_t readTouchZ();

#endif