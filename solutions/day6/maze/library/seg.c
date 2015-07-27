/*! \file seg.c */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 09.04.2009
// Revised		: 29.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//*****************************************************************************

#include "mb96348hs.h"
#include "seg.h"
#include "seg.cfg.h"

static const uint8_t DEC7SEG[16] = { UINT8(~0x3f), UINT8(~0x06), UINT8(~0x5b), UINT8(~0x4f), UINT8(~0x66), UINT8(~0x6d), UINT8(~0x7d), UINT8(~0x07), UINT8(~0x7f), UINT8(~0x6f),
		UINT8(~0x77), UINT8(~0x7c), UINT8(~0x58), UINT8(~0x5e), UINT8(~0x79), UINT8(~0x71) };

void seg_init(void) {
	SEG0_PORT_DB = 0xff;
	SEG0_PORT_DDR = 0xff;
	SEG1_PORT_DB = 0xff;
	SEG1_PORT_DDR = 0xff;
}

void seg_num(uint8_t num) {
	if (num < 100) {
		seg_numLeft(num / 10);
		seg_numRight(num % 10);
	}
}

void seg_numLeft(uint8_t num) {
	if (num < 10)
		SEG1_PORT_DB = DEC7SEG[num];
}

void seg_numRight(uint8_t num) {
	if (num < 10)
		SEG0_PORT_DB = DEC7SEG[num];
}

void seg_hex(uint8_t hex) {
	seg_hexLeft(hex / 16);
	seg_hexRight(hex % 16);
}

void seg_hexLeft(uint8_t hex) {
	if (hex < 16)
		SEG1_PORT_DB = DEC7SEG[hex];
}

void seg_hexRight(uint8_t hex) {
	if (hex < 16)
		SEG0_PORT_DB = DEC7SEG[hex];
}
