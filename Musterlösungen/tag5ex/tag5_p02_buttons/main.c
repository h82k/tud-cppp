#include "mb96348hs.h"

const char DEC7SEG[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
// definitions to increase readability
#define BUTTON_LEFT  PDR07_P0
#define BUTTON_RIGHT PDR07_P1

// define a decimal number consisting of two digits
typedef struct decimal {
	unsigned short units;
	unsigned short tens;
} decimal;

void wait(long time) {
	long i;

	for(i = 0; i < time; i++) {
		__wait_nop();
	}
}

// increment a decimal number
decimal inc(decimal number) {
	decimal result;
	if (number.units == 9 && number.tens == 9) {
		result.units = 0;
		result.tens = 0;
	}
	else {
		if(number.units < 9) {
			result.tens = number.tens;
			result.units = ++number.units;
		}
		else {
			result.tens = ++number.tens;
			result.units = 0;
		}
	}
	return result;
}

// decrement a decimal number
decimal dec(decimal number) {
	decimal result;
	if (number.units == 0 && number.tens == 0) {
		result.units = 9;
		result.tens = 9;
	}
	else {
		if (number.units > 0){
			result.tens = number.tens;
			result.units = --number.units;
		}
		else {
			result.tens = --number.tens;
			result.units = 9;
		}
	}
	return result;
}

// display a decimal number on the seven segment display
void print(decimal number) {
	PDR09 = DEC7SEG[number.tens];
	PDR00 = DEC7SEG[number.units];
}

void main(void) {
	/* your definitions here */
	int prev_left = 1;
	int prev_right = 1;
	decimal number = {0,0};
	
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

	for (;;) {
		/* your code here */
		if (BUTTON_LEFT == 0 && BUTTON_LEFT != prev_left)
			number = dec(number);
		if (BUTTON_RIGHT == 0 && BUTTON_RIGHT != prev_right)
			number = inc(number);
		prev_left = BUTTON_LEFT;
		prev_right = BUTTON_RIGHT;
		print(number);
		wait(10);
	}
	
}
