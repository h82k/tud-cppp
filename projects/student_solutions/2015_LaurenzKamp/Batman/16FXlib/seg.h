/*! \file seg.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 09.04.2009
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
///	\defgroup seg 7-segment display (seg.h)
///	\code #include "seg.h" \endcode
///	\par Overview
///		Routines to show values in decimal or hexadecimal notation on 7 segment displays
///
//*****************************************************************************
//@{
#ifndef SEG_H_
#define SEG_H_

#include "inttypes.h"

/**
 * Initializes I/Os for both seven-segment displays
 */
extern void seg_init(void);

/**
 * Show a decimal number between 0 and 99 on the displays
 * \param num Number to display
 */
extern void seg_num(uint8_t num);

/**
 * Show a decimal digit (0 - 9) on the left display
 * \param num Number to display
 */
extern void seg_numLeft(uint8_t num);

/**
 * Show a decimal digit (0 - 9) on the right display
 * \param num Number to display
 */
extern void seg_numRight(uint8_t num);

/**
 * Show a hexadecimal number between 0 and 255 on the displays
 * \param hex Value to display
 */
extern void seg_hex(uint8_t hex);

/**
 * Show a hexadecimal digit (0 - 15) on the left display
 * \param hex Value to display
 */
extern void seg_hexLeft(uint8_t hex);

/**
 * Show a hexadecimal digit (0 - 15) on the right display
 * \param hex Value to display
 */
extern void seg_hexRight(uint8_t hex);

#endif /* SEG_H_ */
//@}
