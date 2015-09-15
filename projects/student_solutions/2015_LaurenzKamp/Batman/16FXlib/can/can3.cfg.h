/*! \file can3.cfg.h */
//*****************************************************************************
// Author		: Nicolas Weber
// Created		: 29.04.2010
// Revised		: 07.05.2010
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
