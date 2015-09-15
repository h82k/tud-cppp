/*! \file font.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 21.04.2009
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
///	\ingroup lcd
///	\defgroup lcd_font Font (font.h)
/// Used by lcd.h, should not be included directly!
///	\par Overview
///		Defines fontsets for pixelmatrix LCDs.
///
//*****************************************************************************
//@{
#ifndef FONT_H_
#define FONT_H_

#include "inttypes.h"

#define FONT_REGULAR 	0
#define FONT_TINY 		1
#define FONT_NANO 		2

/**
 * Retrieves the array of pages (-> pixels) for the specified ASCII value
 * \param ascii ASCII value
 * \param font Type of font
 * \return 0 if character for value not defined, pointer to the first page for the character otherwise
 */
extern uint8_t* font_getChar(uint8_t ascii, uint8_t font);

extern uint8_t font_getWidth(uint8_t font);
extern uint8_t font_getHeight(uint8_t font);

#endif /* FONT_H_ */
//@}
