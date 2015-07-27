/*! \file interrupts.c */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 12.09.2012
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//*****************************************************************************
#include "mb96348hs.h"
#include "interrupts.h"

extern void InitIrqLevels(void);

#pragma segment DATA=ivt,locate=0x7000
static IRQHandler ivt[256];

static uint8_t initialized = 0;

void interrupts_init(void) {
	uint16_t i;

	if (initialized == 0) {
		interrupts_disable();
		InitIrqLevels();

		for (i = 0; i < 256; i++) {
			ivt[i] = *((IRQHandler)0xFFFC00);
		}

		TBR = ((long)(&ivt[0]) & 0xffff00l) >> 8;

		initialized = 1;

		interrupts_enable();
	}
}

void interrupts_setHandler(uint8_t interruptNr, uint8_t interruptLevel,
		IRQHandler handler) {
	if ((interruptNr < 12) || (interruptNr > 96))
		return;
	if (interruptLevel > 7)
		return;

	ICR = (interruptNr << 8) | interruptLevel;

	ivt[255 - interruptNr] = handler;
}

void interrupts_disableInterrupt(uint8_t interruptNr) {
	ICR = (interruptNr << 8) | 7;
}
