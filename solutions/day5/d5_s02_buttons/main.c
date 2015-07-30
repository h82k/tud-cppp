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

// wait a specified amount of cycles
void wait(long cycle) {
	long i;
	for (i = 0; i < cycle; ++i)
		__wait_nop();
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

// initialize I/O-ports
void initIO(void) {
	PDR00  = 0xff;
	DDR00  = 0xff;		// set port00 as output (right seven-segment display)
	PDR09  = 0xff;
	DDR09  = 0xff;		// set port09 as output (left seven-segment display)
	PDR07  = 0x00;
	DDR07  = 0xfc;		// set P07_0 and P07_1 as input (buttons) - 0xfc = 11111100 (bin)
	PIER07 = 0x03;		// enable input - 0x03 = 00000011 (bin)
}

void main(void) {
	// set the previous state of the buttons to a non-zero (i.e. non pressed) value
	int prev_left = 1;
	int prev_right = 1;
	int cur_left = BUTTON_LEFT;
	int cur_right = BUTTON_RIGHT;
	decimal number = {0,0};
	
	// init buttons and seven-segment displays
	initIO();
	
	for (;;) {
		// buffer the current left button input to avoid problems
		cur_left = BUTTON_LEFT;
		// check whether the left button is pressed comparing with the previous state
		if (cur_left == 0 && cur_left != prev_left)
			number = dec(number);
		
		// buffer the current right button input to avoid problems
		cur_right = BUTTON_RIGHT;
		// check whether the left button is pressed comparing with the previous state 
		if (cur_right == 0 && cur_right != prev_right)
			number = inc(number);
		
		// store the current state of the buttons for the next iteration
		prev_left = cur_left;
		prev_right = cur_right;
		
		// display the number calculated
		print(number);
		
		// wait once
		wait(10);
	}
}
