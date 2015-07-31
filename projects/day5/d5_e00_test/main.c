#include "mb96348hs.h"

const char DEC7SEG[10] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90 };

void main(void) {
	// initialize I/O-ports
	PDR00 = 0xff;
	DDR00 = 0xff; // Set Port00 as output (right 7Segment display)
	PDR09 = 0xff;
	DDR09 = 0xff; // Set Port09 as output (left 7Segment display)
	
	PDR09 = DEC7SEG[4];
	PDR00 = DEC7SEG[2];
	
	for (;;) {
		__wait_nop();
	}
}
