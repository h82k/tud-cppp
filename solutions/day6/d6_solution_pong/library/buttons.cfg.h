/*! \file buttons.cfg.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 20.04.2009
// Revised		: 04.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
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
