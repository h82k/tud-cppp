/*! \file adc.c */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 20.04.2009
// Revised		: 29.06.2009
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
#include "util.h"
#include "adc.h"
#include "adc.cfg.h"

void adc_init(void) {
	// Stop Mode (MD = 11), 8 bit resolution
	ADCS = _BV(ADC_ADCS_MD1) | _BV(ADC_ADCS_MD0) | _BV(ADC_ADCS_S10);
	ADER0 = ADC_PIN_MASK;
}

int16_t adc_getValue(uint8_t pin) {
	uint8_t result = 0;
	if (_BV(pin) & ADC_PIN_MASK) {
		// Setting Register = 011011.......... = 0x6C00 + start address (5 bit) + end address (5 bit)
		ADSR = 0x6c00 | (pin << 5) | pin;
		ADCS |= _BV(ADC_ADCS_STRT) | _BV(ADC_ADCS_BUSY); // start ADC
		while ((ADCS & _BV(ADC_ADCS_INT)) == 0);
		result = ADCR;
		ADCS &= ~_BV(ADC_ADCS_INT);
		return result;
	}
	return -1;
}
