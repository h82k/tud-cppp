/*! \file util.c */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 19.04.2009
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

#include "util.h"
#include "adc.h"
#include "mb96348hs.h"

void delay(uint16_t del) {
	uint16_t cnt;
	for (cnt = 0; cnt < del; cnt++)
		__wait_nop();
}

void delay_us(uint16_t us) {
	TMRLR3 = 7*us - 1;
	TMCSR3 = 0x1403;
	while (TMCSR3_UF == 0)
		__wait_nop();
}

void delay_ms(uint16_t ms) {
	for (; ms > 0; ms--)
		delay_us(1000);
}

void delay_s(uint16_t s) {
	for (; s > 0; s--)
		delay_ms(1000);
}

int sgn(int x) {
	return (x > 0) ? 1 : (x < 0) ? -1 : 0;
}

void intToStr(uint32_t val, uint8_t digits, uint8_t fuellChar, char* dest) {
	uint8_t i;

	if ((digits < 1) || (digits > 10)) {
		dest = 0;
		return;
	}

	for (i = 0; i < digits; i++) {
		dest[digits - i - 1] = '0' + (val % 10);
		val /= 10;
	}

	for (i = 0; i < (digits - 1); i++) {
		if (dest[i] == '0')
			dest[i] = fuellChar;
		else
			break;
	}

	dest[digits] = 0;
}

void intToHex(uint32_t val, uint8_t digits, uint8_t fuellChar, char* dest) {
	uint8_t i;

	if ((digits < 1) || (digits > 8)) {
		dest = 0;
		return;
	}

	for (i = 0; i < digits; i++) {
		dest[digits - i - 1] = '0' + (val % 16);
		if (dest[digits - i - 1] > '9')
			dest[digits - i - 1] += 'A' - ':';
		val /= 16;
	}

	for (i = 0; i < (digits - 1); i++) {
		if (dest[i] == '0')
			dest[i] = fuellChar;
		else
			break;
	}

	dest[digits] = 0;
}


static uint32_t random_w = 0;
static uint32_t random_z = 0;

void random_init(void) {
	uint8_t i;

	adc_init();

	for (i = 0; i < 32; i++) {
		random_w |= (adc_getValue(RANDOM_INIT_PIN_START+(i%RANDOM_INIT_PIN_COUNT)) & 0x01) << i;
		delay_ms(3);
		random_z |= (adc_getValue(RANDOM_INIT_PIN_START+(i%RANDOM_INIT_PIN_COUNT)) & 0x01) << i;
		delay_ms(3);
	}
}

uint32_t random(void)
{
	/*
	 * (Pseudo) random number generation from:
	 * http://en.wikipedia.org/wiki/Random_number_generation#Computational_methods
	 */
    random_z = 36969 * (random_z & 65535) + (random_z >> 16);
    random_w = 18000 * (random_w & 65535) + (random_w >> 16);
    return (random_z << 16) + random_w;  /* 32-bit result */
}

