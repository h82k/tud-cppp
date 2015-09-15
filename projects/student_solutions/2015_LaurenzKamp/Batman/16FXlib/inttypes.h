/*! \file inttypes.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 09.04.2009
// Revised		: 29.06.2009
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
///	\defgroup inttypes Integer types (inttypes.h)
///	\code #include "inttypes.h" \endcode
///	\par Overview
///		Type definitions for integer variables
///
//*****************************************************************************
//@{
#ifndef INTTYPES_H_
#define INTTYPES_H_

/**
 * Unsigned integer, 8 bit
 */
typedef unsigned char uint8_t;

/**
 * Casts a value to an unsigned integer, 8 bit
 */
#define UINT8(x) (uint8_t)(x)

/**
 * Signed integer, 8 bit
 */
typedef char int8_t;

/**
 * Unsigned integer, 16 bit
 */
typedef unsigned int uint16_t;

/**
 * Signed integer, 16 bit
 */
typedef int int16_t;

/**
 * Unsigned integer, 32 bit
 */
typedef unsigned long uint32_t;

/**
 * Signed integer, 32 bit
 */
typedef long int32_t;

#endif /* INTTYPES_H_ */
//@}
