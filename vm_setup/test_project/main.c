#include "mb96348hs.h"

const char DEC7SEG[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
#define DELAY 1000000l

void main(void) {
	/* your definitions here */
	long i, j, d;
	
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
							
	/* your code here */
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {
			// display digits i and j
			PDR09 = DEC7SEG[i];
			PDR00 = DEC7SEG[j];
			// wait DELAY ticks
			for (d = 0; d < DELAY; ++d) {
				__wait_nop();
			}
		}
	}
	
	for (;;) {
		__wait_nop();
	}
	
}
