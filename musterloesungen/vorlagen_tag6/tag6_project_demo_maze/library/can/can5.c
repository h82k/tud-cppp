/*
 * can5.c
 *
 *  Created on: 14.05.2010
 *      Author: Nicolas Weber
 */

#include "can3.h"
#include "can4.h"
#include "can5.h"
#include "../util.h"
#include "mb96348hs.h"

#define CAN5_PING_MSG uint8_t data[4]; data[0] = 'P'; data[1] = 'I'; data[2] = 'N'; data[3] = 'G';
#define CAN5_PING_ANS uint8_t data[4]; data[0] = 'P'; data[1] = 'A'; data[2] = 'N'; data[3] = 'S';

uint32_t pings[2];	//64 max addresses

static uint8_t can5_internal_ping(uint8_t address);
static void can5_irqHandler(void);

uint8_t can5_init(void) {
	if(can4_init(CAN3_MAX_ADDRESS) && can4_open(CAN5_PORT) && can3_registerIRQHandler(&can5_irqHandler) && can5_getNewAddress()) {
		return 1;
	}

	return 0;
}

static uint8_t can5_internal_ping(uint8_t address) {
	uint8_t i;
	CAN5_PING_MSG

	//Clear all ping results
	for(i = 0; i < 2; i++)
		pings[i] = 0;

	return can4_send(address,CAN5_PORT,data,4,0);
}

uint8_t can5_isAlive(uint8_t address) {
	uint16_t timeout = 0;
	
	if(address > 63) return 0;

	//ping
	if(!can5_internal_ping(address)) return 0;

	//wait for answer
	while(((address < 32 ? pings[0] & _BV(address) : pings[1] & _BV(address-32)) == 0) || (timeout++ < CAN5_ALIVE_TIMEOUT))
		delay_us(1);

	//timeout
	if(timeout >= CAN5_ALIVE_TIMEOUT) return 0;

	return 1;
}

uint8_t can5_getNewAddress(void) {
	uint16_t timeout = 0;
	uint8_t i;
	uint8_t check;

	//ping
	if(!can5_internal_ping(CAN3_MULTICAST)) return 0;

	//wait for answers
	delay_us(CAN5_PING_TIMEOUT);

	//get free address
	for(i = 0; i < 64; i++) {
		if(i < 32) 		check = pings[0] & _BV(i);
		else 			check = pings[1] & _BV(i-32);

		if(check == 0) {
			can3_setAddress(i);
			return 1;
		}
	}

	//all addresses used
	return 0;
}

static void can5_irqHandler(void) {
	uint8_t recdata[4];
	uint8_t src;
	uint8_t len;

	len = can4_getData(CAN5_PORT,recdata,&src);

	if(len > 0) {
		if(recdata[0] == 'P' && recdata[1] == 'I' && recdata[2] == 'N' && recdata[3] == 'G') {
			CAN5_PING_ANS
			can4_send(src,CAN5_PORT,data,4,0);
		} else if(recdata[0] == 'P' && recdata[1] == 'A' && recdata[2] == 'N' && recdata[3] == 'S') {
			if(src < 32) 	pings[0] |= _BV(src);
			else 			pings[1] |= _BV(src-32);
		}
	}
}

void can5_close(void) {
	can3_removeIRQHandler(&can5_irqHandler);
	can4_close(CAN5_PORT);
}
