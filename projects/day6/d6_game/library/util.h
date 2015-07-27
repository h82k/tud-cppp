/*! \file util.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 19.04.2009
// Revised		: 05.07.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
/// \ingroup std
///	\defgroup util Generic helper functions (util.h)
///	\code #include "util.h" \endcode
///	\par Overview
///		Generic helper functions and macros
///
//*****************************************************************************
//@{
#ifndef ROUTINES_H_
#define ROUTINES_H_

#include "inttypes.h"

/**
 * Sets the n-th bit of a byte
 * \param bit bit to set
 */
#define _BV(bit) (1l << (bit))

/**
 * Returns 0 if the given value is greater than the given maximal value
 * \param value Value to check
 * \param max Maximum value allowed
 */
#define RETURN_ERROR(value, max) if ((value) > (max)) return 0;

/**
 * Delays for some CPU cycles
 * \param del Delay loop count
 */
extern void delay(uint16_t del);

/**
 * Delays for N microseconds
 * \param us Number of microseconds to delay
 * \note Uses Reload Timer 3!
 */
extern void delay_us(uint16_t us);

/**
 * Delays for N milliseconds based on #delay_us
 * \param ms Number of milliseconds to delay
 */
extern void delay_ms(uint16_t ms);

/**
 * Delays for N seconds based on #delay_ms
 * \param s Number of seconds to delay
 */
extern void delay_s(uint16_t s);

/**
 * Returns 1 for values greater 0, 0 for 0, -1 for values lower 0
 * \param x Value to check
 * \return Signum value of X
 */
extern int sgn(int x);

/**
 * Convert the given integer value (up to 32 bits, unsigned) to the string
 * representing its decimal value.
 * \param val Integer to convert
 * \param digits Number of digits the output string should have (1 - 10)
 * \param fuellChar The character used for digits in front of the value
 * \param dest Pointer to stringbuffer, 0 on errror
 */
extern void intToStr(uint32_t val, uint8_t digits, uint8_t fuellChar, char* dest);

/**
 * Convert the given integer value (up to 32 bits, unsigned) to the string
 * representing its hexadecimal value.
 * \param val Integer to convert
 * \param digits Number of digits the output string should have (1 - 8)
 * \param fuellchar The character used for digits in front of the value
 * \param dest Pointer to stringbuffer, 0 on errror
 */
extern void intToHex(uint32_t val, uint8_t digits, uint8_t fuellchar, char* dest);


/**
 * Initialize the random number generator.
 */
extern void random_init(void);

/**
 * Get a random byte value. The initialization vector is created by reading out
 * up to 4 ADC pins.
 * \return Random value
 * \note #random_init has to be called before the first call to random!
 */
extern uint32_t random(void);

/**
 * Number of ADC pins used for initialization of the RNG.
 */
#define RANDOM_INIT_PIN_COUNT 5

/**
 * First of the ADC pins used for initialization of the RNG.
 */
#define RANDOM_INIT_PIN_START 3

/**
 * Prescaler used by the delay_ms routine to get loops of one millisecond each
 */
#define PRESCALER_MS 1993l

#endif /* ROUTINES_H_ */
//@}
