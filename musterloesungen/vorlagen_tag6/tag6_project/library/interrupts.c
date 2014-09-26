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

#pragma segment DATA=ivt,locate=0x7270
#pragma segment FAR_DATA=ivt,locate=0x7270
static IRQHandler ivt[100];

static uint8_t initialized = 0;

void interrupts_init(void) {
	uint16_t i;

	if (initialized == 0) {
		interrupts_disable();
		InitIrqLevels();

		for (i = 0; i < 100; i++) {
			ivt[i] = *((IRQHandler*) (0xFFFC00ul + 0x270ul + i * 4ul));
		}

		TBR = ((long) (&ivt[0]) & 0xfffc00l) >> 8;

		initialized = 1;

		interrupts_enable();
	}
}

void interrupts_setHandler(uint8_t interruptNr, uint8_t interruptLevel, IRQHandler handler) {
	if ((interruptNr < 12) || (interruptNr > 96))
		return;
	if (interruptLevel > 7)
		return;

	if (initialized == 0)
		interrupts_init();

	ICR = (interruptNr << 8) | interruptLevel;

	ivt[99 - interruptNr] = handler;
}

void interrupts_disableInterrupt(uint8_t interruptNr) {
	if ((interruptNr < 12) || (interruptNr > 96))
		return;

	if (initialized == 0)
		interrupts_init();

	ICR = (interruptNr << 8) | 7;
}
