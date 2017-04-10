#include "segment.h"

#include "mb96348hs.h"

const char DEC7SEG[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void segment_init(void)
{
	PDR00  = 0xff;
	DDR00  = 0xff;		// set port00 as output (right seven-segment display)
	PDR09  = 0xff;
	DDR09  = 0xff;		// set port09 as output (left seven-segment display)
}

void segment_set_left(int i)
{
	PDR09 = DEC7SEG[i];
}

void segment_set_right(int i)
{
	PDR00 = DEC7SEG[i];
}
