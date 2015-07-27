/*! \file inttypes.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 09.04.2009
// Revised		: 29.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
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
