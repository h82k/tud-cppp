/*
 * adc.c
 *
 *  Created on: 10.09.2015
 *      Author: insel
 */

#include "io.h"

#include "mb96348hs.h"

static const char DEC7SEG[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void seg_show(int value)
{
	if(value > 99) {
		value = 99;
	}

	PDR09 = DEC7SEG[value / 10];
	PDR00 = DEC7SEG[value % 10];

	return;
}

void wait(long d)
{
	while(d--) {
		__wait_nop();
	}

	return;
}

// init I/O-ports
void initIO(void) {
	PDR00  = 0xff;
	DDR00  = 0xff;		// set port00 as output (right seven-segment display)
	PDR09  = 0xff;
	DDR09  = 0xff;		// set port09 as output (left seven-segment display)
	PDR07  = 0x00;
	DDR07  = 0xfc;		// set P07_0 and P07_1 as input (buttons) - 0xfc = 11111100 (bin)
	PIER07 = 0x03;		// enable input - 0x03 = 00000011 (bin)
}

// return ADC value of the specified channel (either 1 or 2)
int getADCValue(int channel) {
	int result;
	ADSR = 0x6C00 + (channel << 5) + channel;	// start and end channel is channelNumber
	ADCS_STRT = 1;								// start A/D conversion
	while(ADCS_INT == 0) {} 					// wait for conversion to finish
	result = ADCRL;								// store result (1 byte)
	ADCRL = 0;									// set bit to 0 for next conversion
	return result;
}

// init A/D converter
void initADC(void) {
	ADCS_MD = 3; 		// ADC Stop Mode
	ADCS_S10 = 1;		// 8 Bit Precision
	ADER0_ADE1 = 1;		// Activate analog input AN1 + AN2
	ADER0_ADE2 = 1;		// (ADER0: Inputs AN0 - AN7)
}
