/*! \file adc.c */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 20.04.2009
// Revised		: 29.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
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
