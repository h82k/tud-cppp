/*
 * can3.c
 *
 *  Created on: 23.04.2010
 *      Author: Nicolas Weber
 */

#include "can3.h"
#include "can3.cfg.h"
#include "../util.h"
#include "../interrupts.h"
#include "mb96348hs.h"

#define _AC(x) (((uint32_t)x) << 22)
#define _SC(x) (((uint32_t)x) << 16)
#define CAN3_RETURN_ERROR(x,y) if(x) return y
#define CAN3_RETURN_UBOUNDS(x,max,out) if(x > max) return out
#define CAN3_RETURN_SBOUNDS(x,min,max,out) if(x < min || x > max) return out
#define CAN3_EXTRACT_DESTINATION(id) (uint8_t)((id & 0x0FC00000) >> 22)
#define CAN3_EXTRACT_SOURCE(id) 	 (uint8_t)((id & 0x003F0000) >> 16)
#define CAN3_EXTRACT_ID(id)			 (uint16_t)(id & 0x0000FFFF)
#define CAN3_EXTRACT_MULTICAST(id)	 (uint8_t)((id & 0x10000000) >> 28)
#define CAN3_FREE_BUFFER 255

__interrupt void IRQHandler_CAN (void);

struct DataBuffer {
	uint8_t buffer;
	uint8_t data[8];
	uint8_t source;
	uint8_t len;
	uint16_t id;
};

struct DataBuffer databuffer[CAN3_DATABUFFER_SIZE];

IRQHandler irqHandler[CAN3_MAX_IRQHANDLER];

uint8_t can3_address;
uint32_t can3_usedbuffer;

static void can3_internal_block(uint8_t buffer) {
	can3_usedbuffer |= _BV(buffer - 1);
}

static uint8_t can3_internal_getFreeBuffer(void) {
	uint32_t check;
	uint8_t buffer;

	//check vars
	CAN3_RETURN_UBOUNDS(can3_usedbuffer,0xFFFD,0);		//no free buffer

	//init vars
	check  = 1;
	buffer = 1; //offset, 1-32

	while(check < 0xFFFF) {
		if(!(check & can3_usedbuffer)) {
			return buffer;
		}

		//increment
		check =  check << 1;
		buffer++;
	}

	//should never happen
	return 0;
}

static struct DataBuffer* can3_internal_getFreeDataBuffer(void) {
	uint8_t i;

	for(i = 0; i < CAN3_DATABUFFER_SIZE; i++) {
		if(databuffer[i].buffer == CAN3_FREE_BUFFER)
			return &databuffer[i];
	}

	return 0;
}

static void can3_irqHandler(void) {
	struct DataBuffer* data;
	uint32_t received_id = 0;
	uint8_t buffer = INTR0;

	if(!(_BV(buffer - 1) & can3_usedbuffer)) return;
	if(!(data = can3_internal_getFreeDataBuffer())) return;

	if(can_buffer_newData(buffer)) {
		data->len = can_buffer_getData(buffer, data->data, &received_id);

		//no data or unmatching multicast?
#ifndef CAN3_SKIP_ADDRESS_CHECK
		if(data->len == 0 || (CAN3_EXTRACT_MULTICAST(received_id) == 0 && CAN3_EXTRACT_DESTINATION(received_id) != can3_address)) {
			return;
		}
#endif

		//extract data
		data->buffer = buffer;
		data->source = CAN3_EXTRACT_SOURCE(received_id);
		data->id     = CAN3_EXTRACT_ID(received_id);
	}
}

uint8_t can3_init(uint8_t address) {
	uint8_t i;
	RETURN_ERROR(address,CAN3_MAX_ADDRESS);

	CAN3_RETURN_ERROR(!can_init(CAN3_BAUDRATE,1),0);	//Auto enable interrupts

	interrupts_init();
	interrupts_setLevel(7);
	interrupts_setHandler(33, 2, IRQHandler_CAN);
	interrupts_enable();

	//address
	can3_address = address;

	//buffer
	can3_usedbuffer = 0x0000;

	//init buffer
	for(i = 0; i < CAN3_DATABUFFER_SIZE; i++)
		databuffer[i].buffer = CAN3_FREE_BUFFER;

	//init IRQ Handler
	for(i = 0; i < CAN3_MAX_IRQHANDLER; i++)
		irqHandler[i] = 0;

	can3_registerIRQHandler(&can3_irqHandler);

	return 1;
}

uint8_t can3_send(uint8_t dest, uint16_t uid, uint8_t* data, uint8_t len, uint8_t interrupt) {
	uint8_t buffer;
	uint16_t timeout = 0;
	uint32_t id;
	uint8_t options = CAN_BUF_OPT_ENABLED | CAN_BUF_OPT_EXTENDED | CAN_BUF_OPT_TRANSMIT;

	//checks
	RETURN_ERROR(can3_address,CAN3_MAX_ADDRESS);			//wrong source address

	if(dest != CAN3_MULTICAST) {
		RETURN_ERROR(dest,CAN3_MAX_ADDRESS);			    //wrong destination address
		id 	= _AC(dest) | _SC(can3_address) | (uint32_t)uid;
	} else {
		id	= _BV(28) | _SC(can3_address) | (uint32_t)uid;
	}

	buffer  = can3_internal_getFreeBuffer();

	//cancel if no buffer is free
	if(buffer == 0) return 0;

	if(interrupt) options |= CAN_BUF_OPT_TX_INTERRUPT;

	//configure buffer
	CAN3_RETURN_ERROR(!can_config_buffer(buffer,id,options,0,0),0);

	//set data
	CAN3_RETURN_ERROR(!can_set_buffer_data(buffer,data,len),0);

	//send data
	CAN3_RETURN_ERROR(!can_send_buffer(buffer),0);

	//wait for data be send
	while(((STATR0_TXOK == 0)|| (TREQR0 & _BV(buffer -1) != 0)/* || (INTPND0 != buffer)*/)
			&& (timeout++ < CAN3_SEND_TIMEOUT))
		delay_us(1);

	if(timeout >= CAN3_SEND_TIMEOUT)	//Send Timeout
		return 1;

	return 1;
}

uint8_t can3_open(uint16_t uid) {
	return can3_maskedOpen(uid,0x0000FFFF);
}

uint8_t can3_maskedOpen(uint16_t uid, uint16_t idMask) {
	uint32_t id, mask;
	uint8_t buffer;
	uint8_t options = CAN_BUF_OPT_ENABLED | CAN_BUF_OPT_EXTENDED;

	//check vars
	CAN3_RETURN_UBOUNDS(can3_usedbuffer,0xFFFD,0);			//no free buffer
	CAN3_RETURN_UBOUNDS(can3_address,CAN3_MAX_ADDRESS,0);	//wrong address

	//init addressed id
	id     = (uint32_t)uid;
	mask = 0x00000000 | idMask;

	//set interrupts
	options = options | CAN_BUF_OPT_RX_INTERRUPT;

	//search free buffer
	buffer = can3_internal_getFreeBuffer();

	//lock buffer
	can3_internal_block(buffer);

	//check if everything is right
	CAN3_RETURN_ERROR(!can_config_buffer(buffer,id,options, CAN_BUF_MASK_USE | CAN_BUF_MASK_EXTENDED,idMask),0);

	return buffer;
}

uint8_t can3_getData(uint8_t buffer, uint8_t* data, uint8_t* source, uint16_t* id) {
	uint8_t i, n;

	if(!(_BV(buffer - 1) & can3_usedbuffer)) return 0; //unused buffer

	for(i = 0; i < CAN3_DATABUFFER_SIZE; i++) {
		if(databuffer[i].buffer == buffer) {
			for(n = 0; n < databuffer[i].len; n++) {
				data[n] = databuffer[i].data[n];
			}

			*id 	= databuffer[i].id;
			*source = databuffer[i].source;

			databuffer[i].buffer = CAN3_FREE_BUFFER;

			return databuffer[i].len;
		}
	}

	return 0;
}

uint8_t can3_getAddress(void) {
	return can3_address;
}

void can3_setAddress(uint8_t addr) {
	if(addr > CAN3_MAX_ADDRESS) return;
	can3_address = addr;
}

void can3_close(uint8_t buffer) {
	uint8_t i;
	uint32_t check = _BV(buffer-1);

	if(check & can3_usedbuffer) {
		can3_usedbuffer ^= check;
		can_config_buffer(buffer,0,0,0,0);

		//dismiss data left in databuffer for this canbuffer
		for(i = 0; i < CAN3_DATABUFFER_SIZE; i++) {
			if(databuffer[i].buffer == buffer)
				databuffer[i].buffer = CAN3_FREE_BUFFER;
		}
	}
}

uint8_t can3_registerIRQHandler(IRQHandler func) {
	uint8_t i;

	for(i = 0; i < CAN3_MAX_IRQHANDLER; i++) {
		if(irqHandler[i] == 0) {
			irqHandler[i] = func;
			return 1;
		}
	}

	return 0;
}

uint8_t can3_removeIRQHandler(IRQHandler func) {
	uint8_t i;

	for(i = 0; i < CAN3_MAX_IRQHANDLER; i++) {
		if(irqHandler[i] == func) {
			irqHandler[i] = 0;
			return 1;
		}
	}

	return 0;
}

__interrupt
void IRQHandler_CAN (void) {
	uint16_t source = INTR0;

	if (source == 0x8000) {
		//STATUS INTERRUPT
		source = STATR0;

		// Read the Status Register
		// This will also clear pending Status/Error Interrupt
		if ((source & 0x80) == 0x80) { // BusOff??
			// Busoff handling
		}

		if ((source & 0x40) == 0x40) { // Error Warning??
			// Error Warning handling
		}

		if ((source & 0x20) == 0x20) { // Error Passive??
			// Error Passive handling
		}

		if ((source & 0x10) == 0x10) { // RXOK??
			// Clear RXOK Flag in Status register
			STATR0_RXOK = 0;
		}

		if ((source & 0x08) == 0x08) { // TXOK??
			// Clear TXOK Flag in Status register
			STATR0_TXOK = 0;
		}

		if ((source & 0x07) != 0x00) { // LEC??
			// Clear LEC in Status register
			STATR0_LEC = 0;
		}
	} else if ((source - 1) < 32) {
		uint8_t i;

		for(i = 0; i < CAN3_MAX_IRQHANDLER; i++) {
			if(irqHandler[i] != 0) {
				(*irqHandler[i])();
			}
		}
	}
}
