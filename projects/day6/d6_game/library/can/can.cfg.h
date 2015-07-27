/*! \file can.cfg.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 04.05.2009
// Revised		: 29.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
///	\ingroup can_lowlevel
///	\defgroup can_lowlevel_configuration Internal configurations (can.cfg.h)
///	\par Overview
///		This library provides hardware definitions to the low level CAN library.
///
//*****************************************************************************
//@{


#ifndef CAN_CFG_H_
#define CAN_CFG_H_

#include "mb96348hs.h"

/// Input enable register which contains the CAN input pin
#define CAN_RX_ENABLE	PIER10
/// Bit in the input enable register of the CAN input pin
#define CAN_RX_BIT		0

/// Base register of the CAN controller to be used (CTRLRx)
#define CAN_BASE	CTRLR0
/// Number of CAN buffers in the CAN engine of the controller
#define CAN_BUFFERCOUNT	32



/// Calculates the register (including appropriate type) based on #CAN_BASE and the register offset
#define CANREG(x)   (*((CAN_##x##_TYPE*)((uint8_t*)(&(CAN_BASE)) + CAN_##x##_OFFSET)))


// TODO: Documentation for registers / bits

#define CAN_COER_OFFSET	0xCE
#define CAN_COER_TYPE	uint8_t
#define CAN_COER	CANREG(COER)
#define CAN_COER_OE		0

#define CAN_CTRLR_OFFSET	0x00
#define CAN_CTRLR_TYPE	uint8_t
#define CAN_CTRLR	CANREG(CTRLR)
#define CAN_CTRLR_INIT	0
#define CAN_CTRLR_IE	1
#define CAN_CTRLR_SIE	2
#define CAN_CTRLR_EIE	3
#define CAN_CTRLR_DAR	5
#define CAN_CTRLR_CCE	6
#define CAN_CTRLR_TEST	7

#define CAN_STATR_OFFSET	0x02
#define CAN_STATR_TYPE	uint8_t
#define CAN_STATR	CANREG(STATR)
#define CAN_STATR_LEC_MASK	(0x07)
#define CAN_STATR_TXOK	3
#define CAN_STATR_RXOK	4
#define CAN_STATR_EPASS	5
#define CAN_STATR_EWARN	6
#define CAN_STATR_BOFF	7

#define CAN_ERRCNTH_OFFSET	0x05
#define CAN_ERRCNTH_TYPE	uint8_t
#define CAN_ERRCNTH	CANREG(ERRCNTH)
#define CAN_ERRCNTH_RP	7
#define CAN_ERRCNTH_REC_MASK	(0x7f)

#define CAN_ERRCNTL_OFFSET	0x04
#define CAN_ERRCNTL_TYPE	uint8_t
#define CAN_ERRCNTL	CANREG(ERRCNTL)

#define CAN_BTR_OFFSET	0x06
#define CAN_BTR_TYPE	uint16_t
#define CAN_BTR	CANREG(BTR)
#define CAN_BTR_TSEG2_MASK	(0x7000)
#define CAN_BTR_TSEG2_SHIFT	(12)
#define CAN_BTR_TSEG1_MASK	(0x0f00)
#define CAN_BTR_TSEG1_SHIFT	(8)
#define CAN_BTR_SJW_MASK	(0x00c0)
#define CAN_BTR_SJW_SHIFT	(6)
#define CAN_BTR_BRP_MASK	(0x003f)

#define CAN_INTR_OFFSET	0x08
#define CAN_INTR_TYPE	uint16_t
#define CAN_INTR	CANREG(INTR)
#define CAN_INTR_STATUS_VALUE	0x8000

#define CAN_TESTR_OFFSET	0x0A
#define CAN_TESTR_TYPE	uint8_t
#define CAN_TESTR	CANREG(TESTR)
#define CAN_TESTR_RX	7
#define CAN_TESTR_TX1	6
#define CAN_TESTR_TX0	5
#define CAN_TESTR_LBACK	4
#define CAN_TESTR_SILENT	3
#define CAN_TESTR_BASIC	2

#define CAN_BRPER_OFFSET	0x0C
#define CAN_BRPER_TYPE	uint8_t
#define CAN_BRPER	CANREG(BRPER)



#define CAN_IF1CREQ_OFFSET	0x10
#define CAN_IF1CREQ_TYPE	uint8_t
#define CAN_IF1CREQ	CANREG(IF1CREQ)
#define CAN_IF1CMSK_OFFSET	0x12
#define CAN_IF1CMSK_TYPE	uint8_t
#define CAN_IF1CMSK	CANREG(IF1CMSK)
#define CAN_IF1MSK_OFFSET	0x14
#define CAN_IF1MSK_TYPE	uint32_t
#define CAN_IF1MSK	CANREG(IF1MSK)
#define CAN_IF1ARB_OFFSET	0x18
#define CAN_IF1ARB_TYPE	uint32_t
#define CAN_IF1ARB	CANREG(IF1ARB)
#define CAN_IF1MCTR_OFFSET	0x1C
#define CAN_IF1MCTR_TYPE	uint16_t
#define CAN_IF1MCTR	CANREG(IF1MCTR)
#define CAN_IF1DTA_OFFSET	0x1E
#define CAN_IF1DTA_TYPE	uint32_t
#define CAN_IF1DTA	CANREG(IF1DTA)
#define CAN_IF1DTB_OFFSET	0x22
#define CAN_IF1DTB_TYPE	uint32_t
#define CAN_IF1DTB	CANREG(IF1DTB)

#define CAN_IF2CREQ_OFFSET	0x40
#define CAN_IF2CREQ_TYPE	uint8_t
#define CAN_IF2CREQ	CANREG(IF2CREQ)
#define CAN_IF2CMSK_OFFSET	0x42
#define CAN_IF2CMSK_TYPE	uint8_t
#define CAN_IF2CMSK	CANREG(IF2CMSK)
#define CAN_IF2MSK_OFFSET	0x44
#define CAN_IF2MSK_TYPE	uint32_t
#define CAN_IF2MSK	CANREG(IF2MSK)
#define CAN_IF2ARB_OFFSET	0x48
#define CAN_IF2ARB_TYPE	uint32_t
#define CAN_IF2ARB	CANREG(IF2ARB)
#define CAN_IF2MCTR_OFFSET	0x4C
#define CAN_IF2MCTR_TYPE	uint16_t
#define CAN_IF2MCTR	CANREG(IF2MCTR)
#define CAN_IF2DTA_OFFSET	0x4E
#define CAN_IF2DTA_TYPE	uint32_t
#define CAN_IF2DTA	CANREG(IF2DTA)
#define CAN_IF2DTB_OFFSET	0x52
#define CAN_IF2DTB_TYPE	uint32_t
#define CAN_IF2DTB	CANREG(IF2DTB)

#define CAN_IFCREQ_BUSY	15

#define CAN_IFCMSK_WRRD	7
#define CAN_IFCMSK_MASK	6
#define CAN_IFCMSK_ARB	5
#define CAN_IFCMSK_CONTROL	4
#define CAN_IFCMSK_CIP	3
#define CAN_IFCMSK_TXREQ	2
#define CAN_IFCMSK_DATAA	1
#define CAN_IFCMSK_DATAB	0

#define CAN_IFMSK_MXTD	31
#define CAN_IFMSK_MDIR	30
#define CAN_IFMSK_MSK_MASK	(0x1fffffffL)

#define CAN_IFARB_MSGVAL	31
#define CAN_IFARB_XTD	30
#define CAN_IFARB_DIR	29
#define CAN_IFARB_ID_MASK	(0x1fffffffL)

#define CAN_IFMCTR_NEWDAT	15
#define CAN_IFMCTR_MSGLST	14
#define CAN_IFMCTR_INTPNT	13
#define CAN_IFMCTR_UMASK	12
#define CAN_IFMCTR_TXIE	11
#define CAN_IFMCTR_RXIE	10
#define CAN_IFMCTR_RMTEN	9
#define CAN_IFMCTR_TXRQST	8
#define CAN_IFMCTR_EOB	7
#define CAN_IFMCTR_DLC_MASK	(0x000f)



#define CAN_TREQR_OFFSET	0x80
#define CAN_TREQR_TYPE	uint32_t
#define CAN_TREQR	CANREG(TREQR)
#define CAN_NEWDT_OFFSET	0x90
#define CAN_NEWDT_TYPE	uint32_t
#define CAN_NEWDT	CANREG(NEWDT)
#define CAN_INTPND_OFFSET	0xA0
#define CAN_INTPND_TYPE	uint32_t
#define CAN_INTPND	CANREG(INTPND)
#define CAN_MSGVAL_OFFSET	0xB0
#define CAN_MSGVAL_TYPE	uint32_t
#define CAN_MSGVAL	CANREG(MSGVAL)



#endif /* CAN_CFG_H_ */
//@}
