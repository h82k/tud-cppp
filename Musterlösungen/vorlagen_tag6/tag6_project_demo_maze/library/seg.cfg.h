/*! \file seg.cfg.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 20.04.2009
// Revised		: 04.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
///	\ingroup seg
///	\defgroup seg_configuration Internal configurations (seg.cfg.h)
///	\par Overview
///		This library provides hardware definitions for the 7 segment display code.
///
//*****************************************************************************
//@{
#ifndef SEG_CFG_H_
#define SEG_CFG_H_

/// Port of the first 7seg
#define SEG0_PORT_DB	PDR00
/// Data direction register for the first 7seg
#define SEG0_PORT_DDR	DDR00
/// Port of the second 7seg
#define SEG1_PORT_DB	PDR09
/// Data direction register for the second 7seg
#define SEG1_PORT_DDR	DDR09

#endif /* SEG_CFG_H_ */
//@}
