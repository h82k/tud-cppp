#include "mb96348hs.h"

const char DEC7SEG[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
#define DELAY 300000l
// definitions to increase readability
#define BUTTON_LEFT  PDR07_P0
#define BUTTON_RIGHT PDR07_P1
#define SEG_LEFT PDR09
#define SEG_RIGHT PDR00


/* your functions here */
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

// increment an integer not exceeding 99
int inc(int i) {
	if(i < 99)
		return ++i;
	else
		return 0;
}

// decrement an integer not falling below 0
int dec(int i) {
	if(i > 0)
		return --i;
	else
		return 99;
}

void main(void) {
	/* definitions go here */
	int number = 0;
	int prev_left = 1;
	int prev_right = 1;
	int cur_left = BUTTON_LEFT;
	int cur_right = BUTTON_RIGHT;
	
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
		/* your code gere */
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
		set7Seg(number);
		
		// wait once
		wait(10);
	}
	
}
