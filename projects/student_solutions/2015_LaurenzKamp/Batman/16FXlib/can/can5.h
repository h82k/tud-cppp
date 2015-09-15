/*! \file can5.h */
//*****************************************************************************
// Author		: Nicolas Weber
// Created		: 14.05.2010
// Revised		: 14.05.2010
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
///	\ingroup can
///	\defgroup can_systemservices CAN System Services (can5.h)
///	\par Overview
///		This library enables System Services.
///
//*****************************************************************************
//@{

#ifndef CAN5_H_
#define CAN5_H_

#include "../inttypes.h"

/**
 * Initializes the CAN controller. Also optains automatically an address for this controller. Interrupts are also activated.
 * \return 1 if everything went fine, 0 if there was an error
 */
uint8_t can5_init(void);

/**
 * Closes the standard system message port (port 0)
 */
void can5_close(void);

/**
 * Checks if given address is online.
 * \param address Address to be used
 * \return 1 if address is online, 0 if is offline
 */
uint8_t can5_isAlive(uint8_t address);

/**
 * Internal address to optain new address but can also be accessed from outside.
 * \return 1 if everything went fine, 0 if there was an error
 */
uint8_t can5_getNewAddress(void);

/** @name Service variables
 *
 */
//@{
	#define CAN5_PING_TIMEOUT 200000
	#define CAN5_ALIVE_TIMEOUT 20000
	#define CAN5_PORT 0
//@}

#endif
//@}
