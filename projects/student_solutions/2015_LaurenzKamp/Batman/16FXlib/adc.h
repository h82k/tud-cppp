/*! \file adc.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 20.04.2009
// Revised		: 06.06.2009
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
