/*! \file buttons.h */
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
 * \param pin Pin number (0 = left button, 1 = right button)
 * \return 1 if pressed, 0 if released, -1 if wrong pin number
 */
extern int8_t buttons_get(uint8_t pin);

/**
 * Check if button on pin N was pressed down since the last call
 * \param pin Pin number (0 = left button, 1 = right button)
 * \return 1 if button was pressed down since last call, -1 if wrong pin number, 0 otherwise
 */
extern int8_t buttons_event(uint8_t pin);

#endif /* BUTTONS_H_ */
//@}
