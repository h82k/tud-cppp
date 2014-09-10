/*! \file adc.cfg.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 20.04.2009
// Revised		: 29.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
///	\ingroup adc
///	\defgroup adc_configuration Internal configurations (adc.cfg.h)
///	\par Overview
///		This library provides hardware definitions to the ADC code.
///
//*****************************************************************************
//@{

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/// ADC busy bit. 1 while conversion is running. Write to 0 to force stop conversion
#define ADC_ADCS_BUSY	15
/// ADC interrupt flag
#define ADC_ADCS_INT	14
/// ADC interrupt enable
#define ADC_ADCS_INTE	13
/// ADC pause bit
#define ADC_ADCS_PAUS	12
/// ADC start source select 1
#define ADC_ADCS_STS1	11
/// ADC start source select 0
#define ADC_ADCS_STS0	10
/// ADC start conversion
#define ADC_ADCS_STRT	9
/// ADC converter mode 1
#define ADC_ADCS_MD1	7
/// ADC converter mode 0
#define ADC_ADCS_MD0	6
/// ADC 8 bit mode
#define ADC_ADCS_S10	5

/// ADC usable pins mask
#define ADC_PIN_MASK	0xff //(_BV(1) | _BV(2))


#endif /* ADC_CFG_H_ */
//@}
