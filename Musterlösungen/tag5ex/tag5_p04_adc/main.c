#include "mb96348hs.h"

const char DEC7SEG[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
#define DELAY 300000l
// definitions to increase readability
#define SEG_LEFT PDR09
#define SEG_RIGHT PDR00

// wait a specified amount of cycles
void wait(long cycle) {
	long i;
	for (i = 0; i < cycle; ++i)
		__wait_nop();
}

// set the left seven segment display
void setLeft7Seg(int i) {
	if (i > 9 || i < 0)
		return;
	SEG_LEFT = DEC7SEG[i];
}

// set the right seven segment display
void setRight7Seg(int i) {
	if (i > 9 || i < 0)
		return;
	SEG_RIGHT = DEC7SEG[i];
}

// set both seven segment displays
void set7Seg(int i) {
	// determine units and tens
	// note checking whether i is greater than 99 is omitted here
	// but implemented in the set seven segment display methods
	int units = i % 10;
	int tens = (i - units) / 10;
	// display i on both seven segment displays
	setLeft7Seg(tens);
	setRight7Seg(units);
}

// scale from 0-255 to 0-9
int scaleInt(int num) {
	return (num * 10) / 256;
}

//returns the value for specified channel
int getADValue(int channel) {
	int result;
	
	ADSR = 0x6C00 + (channel << 5) + channel; 			  // Start and end channel is channelNumber
	ADCS_STRT = 1;										  // Start A/D conversion
	while(ADCS_INT == 0) {} 							  // Wait for conversion to finish
	result = ADCRL;										  // Store result (1 Byte)
	ADCRL = 0;										      // Set bit to 0 for next conversion
	return result;
}

void main(void) {
	/* definitions go here */
	int value;

	// initialize I/O-ports
	PDR00  = 0xff;
	DDR00  = 0xff;		// Set Port00 as output (right 7Segment display)
	PDR09  = 0xff;
	DDR09  = 0xff;		// Set Port09 as output (left 7Segment display)

	PDR07  = 0x00;
	DDR07  = 0xfc;		// Set P07_0 and P07_1 as input (buttons)
							// 0xfc = 11111100 (bin)
	PIER07 = 0x03;		// enable input
							// 0x03 = 00000011 (bin)

	// Initialisation of AD converter
	ADCS_MD = 3; 		// ADC Stop Mode
	ADCS_S10 = 1;		// 8 Bit Precision
	ADER0_ADE1 = 1;		// Activate analog input AN1 + AN2
	ADER0_ADE2 = 1;		// (ADER0: Inputs AN0 - AN7)

	for (;;) {
		// read the AD value from channel 1 and display its value
		value = getADValue(1);
		setLeft7Seg(scaleInt(value));
		
		wait(5);
		
		// read the AD value from channel 2 and display its value
		value = getADValue(2);
		setRight7Seg(scaleInt(value));
		
		wait(5);

	}

}
