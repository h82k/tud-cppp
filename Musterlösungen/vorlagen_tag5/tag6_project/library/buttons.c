/*! \file buttons.c */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 20.04.2009
// Revised		: 04.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//*****************************************************************************

#include "mb96348hs.h"
#include "buttons.h"
#include "buttons.cfg.h"

void buttons_init(void) {
	BUTTONS_PORT = 0x00;
	BUTTONS_DDR = ~(BUTTON_MASK);
	BUTTONS_PIER = BUTTON_MASK;
}

int8_t buttons_get(uint8_t pin) {
	if (_BV(pin) & BUTTON_MASK)
		return ((~BUTTONS_PORT) & _BV(pin)) >> pin;
	return -1;
}

int8_t buttons_event(uint8_t pin) {
	static uint8_t buttonState = 0xff;
	if (_BV(pin) & BUTTON_MASK) {
		uint8_t s = buttons_get(pin);
		if (s != ((buttonState >> pin) & 1)) {
			buttonState &= ~(1 << pin);
			buttonState |= s << pin;
			if (s == 1)
				return 1;
		}
		return 0;
	}
	return -1;
}
