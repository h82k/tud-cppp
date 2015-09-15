/*! \file buttons.cfg.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 20.04.2009
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
///	\ingroup buttons
///	\defgroup buttons_configuration Internal configurations (buttons.cfg.h)
///	\par Overview
///		This library provides hardware definitions to the buttons code.
///
//*****************************************************************************
//@{
#ifndef BUTTONS_CFG_H_
#define BUTTONS_CFG_H_

#include "util.h"

/// Port used by the buttons
#define BUTTONS_PORT	PDR07
/// Direction register for the port
#define BUTTONS_DDR		DDR07
/// Input enable register for the port
#define BUTTONS_PIER	PIER07

/// Button 0 bit
#define BUTTON_0		0
/// Button 1 bit
#define BUTTON_1		1
/// Button mask
#define BUTTON_MASK		(_BV(BUTTON_0) | _BV(BUTTON_1))

#endif /* BUTTONS_CFG_H_ */
//@}
