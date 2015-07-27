/*! \file buttons.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 20.04.2009
// Revised		: 06.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
///	\defgroup buttons Buttons (buttons.h)
///	\code #include "buttons.h" \endcode
///	\par Overview
///		Routines to initialize and query the buttons
///
//*****************************************************************************
//@{
#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "inttypes.h"

/**
 * Initializes I/Os for buttons
 */
extern void buttons_init(void);

/**
 * Get the state of the button on pin N
 * \param pin Pin number
 * \return 1 if pressed, 0 if released, -1 if wrong pin number
 */
extern int8_t buttons_get(uint8_t pin);


#endif /* BUTTONS_H_ */
//@}
