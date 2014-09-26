/*! \file adc.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 20.04.2009
// Revised		: 06.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
///	\defgroup adc ADC (adc.h)
///	\code #include "adc.h" \endcode
///	\par Overview
///		Routines to initialize the Analog-Digital-Converter and do single channel
/// conversions.
///
//*****************************************************************************
//@{

#ifndef ADC_H_
#define ADC_H_

#include "inttypes.h"

/**
 * Initializes the A/D converter
 */
extern void adc_init(void);

/**
 * Gets the value of an A/D conversion for an analog input pin
 *
 * @param pin Input pin AN*
 * @return Result of A/D conversion (8 bit) or -1 if an error occured
 */
extern int16_t adc_getValue(uint8_t pin);

#endif /* ADC_H_ */
//@}
