/*! \file can3.cfg.h */
//*****************************************************************************
// Author		: Nicolas Weber
// Created		: 29.04.2010
// Revised		: 07.05.2010
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
///	\ingroup can_routinglevel
///	\defgroup can_routinglevel_configuration Internal configurations (can3.cfg.h)
///	\par Overview
///		This library enables addressed messaging over the CAN Controller.
///
//*****************************************************************************
//@{
#ifndef CAN3_CFG_H_
#define CAN3_CFG_H_

#define CAN3_BAUDRATE CAN_BAUD_50K
#define CAN3_SEND_TIMEOUT 20000
#define CAN3_MAX_IRQHANDLER 2
#define CAN3_DATABUFFER_SIZE 8
//#define CAN3_SKIP_ADDRESS_CHECK

#endif /* CAN3_CFG_H_ */
//@}
