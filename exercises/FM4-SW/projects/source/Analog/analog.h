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

uint8_t u8Data;        // latest ADC result - global variable for debugging
uint8_t old;           // old value of scan.
uint8_t analog11;
uint8_t analog12;
uint8_t analog13;
uint8_t analog16;
uint8_t analog19;
uint8_t analog23;
uint8_t analog17;

void InitAdc();
void pollData(uint32_t *u32Data);
void getAnalogValues(uint8_t *analog11, uint8_t *analog12, uint8_t *analog13, uint8_t *analog16, uint8_t *analog17,  uint8_t *analog19, uint8_t *analog23);
uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);
uint16_t readTouchX();
uint16_t readTouchY();
uint16_t readTouchZ();


#endif /* ANALOG_H */