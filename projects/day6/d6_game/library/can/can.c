/*! \file can.c */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 04.05.2009
// Revised		: 05.07.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//*****************************************************************************


#include "../util.h"
#include "can.h"
#include "can.cfg.h"


void accessBuffer(uint8_t buffer) {
	CAN_IF1CREQ = buffer;
	while ((CAN_IF1CREQ & _BV(CAN_IFCREQ_BUSY))) {};
}
#pragma inline accessBuffer


uint8_t can_init(uint8_t prescaler, uint8_t propSeg, uint8_t phSeg1, uint8_t phSeg2,
		uint8_t jumpWidth, uint8_t interrupts) {
	uint8_t i;

	RETURN_ERROR(phSeg2 - 1, 7)
	RETURN_ERROR(phSeg1 - 1, 7)
	RETURN_ERROR(propSeg - 1, 7)
	RETURN_ERROR(jumpWidth - 1, 3)
	RETURN_ERROR(prescaler - 1, 63)

	// Enable CAN output pin
	CAN_COER |= _BV(CAN_COER_OE);

	// Enable CAN input pin
	CAN_RX_ENABLE |= _BV(CAN_RX_BIT);

	// Stop CAN operation and set to initialization mode
	CAN_CTRLR = _BV(CAN_CTRLR_INIT);

	// Setup CAN channel Configuration
	CAN_CTRLR |= _BV(CAN_CTRLR_CCE);
	if (interrupts)
		CAN_CTRLR |= _BV(CAN_CTRLR_EIE) | _BV(CAN_CTRLR_IE) | _BV(CAN_CTRLR_SIE);
	CAN_BTR = (prescaler - 1) & CAN_BTR_BRP_MASK;
	CAN_BTR |= ((propSeg + phSeg1 - 1) << CAN_BTR_TSEG1_SHIFT) & CAN_BTR_TSEG1_MASK;
	CAN_BTR |= ((phSeg2 - 1) << CAN_BTR_TSEG2_SHIFT) & CAN_BTR_TSEG2_MASK;
	CAN_BTR |= ((jumpWidth - 1) << CAN_BTR_SJW_SHIFT) & CAN_BTR_SJW_MASK;
	//	CAN_BTR = btr;
	CAN_CTRLR &= ~_BV(CAN_CTRLR_CCE);

	// Disable Message buffers
	for (i = 0; i < CAN_BUFFERCOUNT; i++) {
		CAN_IF1ARB &= ~_BV(CAN_IFARB_MSGVAL);
		CAN_IF1CMSK = _BV(CAN_IFCMSK_WRRD) | _BV(CAN_IFCMSK_ARB);
		accessBuffer(i+1);
	}

	// Start CAN operation
	CAN_CTRLR &= ~_BV(CAN_CTRLR_INIT);

	return 1;
}

uint8_t can_config_buffer(uint8_t buffer, uint32_t id, uint8_t options, uint8_t maskOptions,
		uint32_t idMask) {
	CAN_IF1MCTR = 0;

	RETURN_ERROR(buffer - 1, 31)
	RETURN_ERROR(id, 0x1FFFFFFF)
	RETURN_ERROR(idMask, 0x1FFFFFFF)

	// Set CAN-ID
	if ((options & CAN_BUF_OPT_EXTENDED)) {
		CAN_IF1ARB = ID_TO_EXTFRAME(id) & CAN_IFARB_ID_MASK;
		CAN_IF1ARB |= _BV(CAN_IFARB_XTD);
		CAN_IF1MSK = ID_TO_EXTFRAME(idMask) & CAN_IFMSK_MSK_MASK;
	} else {
		CAN_IF1ARB = ID_TO_STDFRAME(id);
		CAN_IF1MSK = ID_TO_STDFRAME(idMask) & CAN_IFMSK_MSK_MASK;
	}

	// Set direction
	if ((options & CAN_BUF_OPT_TRANSMIT))
		CAN_IF1ARB |= _BV(CAN_IFARB_DIR);

	// Enable buffer
	if ((options & CAN_BUF_OPT_ENABLED))
		CAN_IF1ARB |= _BV(CAN_IFARB_MSGVAL);

	// Use filter mask
	if ((maskOptions & CAN_BUF_MASK_USE))
		CAN_IF1MCTR |= _BV(CAN_IFMCTR_UMASK);
	// Mask direction bit
	if ((maskOptions & CAN_BUF_MASK_DIRECTION))
		CAN_IF1MSK |= _BV(CAN_IFMSK_MDIR);
	// Mask extended bit
	if ((maskOptions & CAN_BUF_MASK_EXTENDED))
		CAN_IF1MSK |= _BV(CAN_IFMSK_MXTD);

	// Enable RX interrupt
	if ((options & CAN_BUF_OPT_RX_INTERRUPT))
		CAN_IF1MCTR |= _BV(CAN_IFMCTR_RXIE);
	// Enable TX interrupt
	if ((options & CAN_BUF_OPT_TX_INTERRUPT))
		CAN_IF1MCTR |= _BV(CAN_IFMCTR_TXIE);

	// Set buffer to single buffer mode
	CAN_IF1MCTR |= _BV(CAN_IFMCTR_EOB);

	// Interface to buffer transfer setup
	CAN_IF1CMSK = _BV(CAN_IFCMSK_WRRD) | _BV(CAN_IFCMSK_MASK) | _BV(CAN_IFCMSK_ARB)
			| _BV(CAN_IFCMSK_CONTROL);

	// Start transfer from interface register to message buffer
	accessBuffer(buffer);

	return 1;
}

uint8_t can_set_buffer_autoreply(uint8_t buffer, uint8_t enable) {
	RETURN_ERROR(buffer - 1, 31)

	// Read current state of MCTR
	CAN_IF1CMSK = _BV(CAN_IFCMSK_CONTROL);
	accessBuffer(buffer);

	// Enable auto reply for RTR
	if (enable)
		CAN_IF1MCTR |= _BV(CAN_IFMCTR_RMTEN);
	else
		CAN_IF1MCTR &= ~_BV(CAN_IFMCTR_RMTEN);

	// Interface to buffer transfer setup
	CAN_IF1CMSK = _BV(CAN_IFCMSK_WRRD) | _BV(CAN_IFCMSK_CONTROL);

	// Start transfer from interface register to message buffer
	accessBuffer(buffer);

	return 1;
}

uint8_t can_set_buffer_data(uint8_t buffer, uint8_t* data, uint8_t len) {
	RETURN_ERROR(buffer - 1, 31)
	RETURN_ERROR(len, 8)

	// Read current state of MCTR
	CAN_IF1CMSK = _BV(CAN_IFCMSK_CONTROL);
	accessBuffer(buffer);

	// Clear DLC bits and set new value
	CAN_IF1MCTR &= ~CAN_IFMCTR_DLC_MASK;
	CAN_IF1MCTR |= len & CAN_IFMCTR_DLC_MASK;

	// Set Data
	CAN_IF1DTA = *((uint32_t*) data);
	CAN_IF1DTB = *((uint32_t*) (data + 4));

	// Interface to buffer transfer setup
	CAN_IF1CMSK = _BV(CAN_IFCMSK_WRRD) | _BV(CAN_IFCMSK_CONTROL) | _BV(CAN_IFCMSK_DATAA)
			| _BV(CAN_IFCMSK_DATAB);

	// Start transfer from interface register to message buffer
	accessBuffer(buffer);

	return 1;
}

uint8_t can_send_buffer(uint8_t buffer) {
	RETURN_ERROR(buffer - 1, 31)

	CAN_IF1CMSK = _BV(CAN_IFCMSK_CONTROL);
	accessBuffer(buffer);

	// TODO: check if newdat should always be set
	CAN_IF1MCTR |= _BV(CAN_IFMCTR_NEWDAT);

	// Interface to buffer transfer setup
	CAN_IF1CMSK = _BV(CAN_IFCMSK_WRRD) | _BV(CAN_IFCMSK_CONTROL) | _BV(CAN_IFCMSK_TXREQ);

	// Start transfer from interface register to message buffer
	accessBuffer(buffer);

	return 1;
}


uint8_t can_buffer_newData(uint8_t buffer) {
	uint8_t i = 1;
	uint32_t tmp = CAN_NEWDT;

	if (buffer > CAN_BUFFERCOUNT)
		return 0;
	if (buffer > 0)
		return (tmp & _BV(buffer-1)) > 0 ? buffer : 0;

	if (tmp) {
		for (; (tmp & 1) == 0; tmp >> 1, i++);
		return i;
	}
	return 0;
}

int8_t can_buffer_getData(uint8_t buffer, uint8_t* data, uint32_t* id) {
	uint8_t len;

	if (buffer - 1 > 31)
		return -1;

	CAN_IF1CMSK = _BV(CAN_IFCMSK_CONTROL) | _BV(CAN_IFCMSK_ARB) | _BV(CAN_IFCMSK_CIP) | _BV(CAN_IFCMSK_TXREQ) | _BV(CAN_IFCMSK_DATAB) | _BV(CAN_IFCMSK_DATAA);
	accessBuffer(buffer);

	len = (uint8_t)(CAN_IF1MCTR & CAN_IFMCTR_DLC_MASK);

	*((uint32_t*) data) = CAN_IF1DTA;
	*((uint32_t*) (data + 4)) = CAN_IF1DTB;

	*id = CAN_IF1ARB & CAN_IFARB_ID_MASK;

	return len;
}

