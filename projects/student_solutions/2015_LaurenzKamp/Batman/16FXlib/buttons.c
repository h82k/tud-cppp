/*! \file buttons.c */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 20.04.2009
// Revised		: 04.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
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
