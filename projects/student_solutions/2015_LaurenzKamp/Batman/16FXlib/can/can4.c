//*****************************************************************************
// Author		: Nicolas Weber
// Created		: 29.04.2010
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
//*****************************************************************************

#ifndef CAN4_C_
#define CAN4_C_
#include "can3.h"
#include "can4.h"
#include "can4.cfg.h"
#include "../util.h"

#define CAN4_EXTRACT_NUMBER(id) (uint8_t) ((id & 0x0000F800) >> 11)
#define CAN4_EXTRACT_COUNT(id)  (uint8_t) ((id & 0x000007C0) >> 6)

#define _PV(x) ((uint16_t)x) << 1
#define _NV(x) ((uint16_t)x) << 11
#define _CV(x) ((uint16_t)x) << 6

#define CAN4_RETURN_UBOUNDS(x,max,out) if(x > max) return out

#define CAN4_BUF_MSG_UNUSED 0xFF
#define CAN4_BUF_UNUSED 0xFF
#define CAN4_BUF_EOM 0xEE

//#define CAN4_EXTRACT_PORT(msg) 			 (msg & 0x0000001F)
//#define CAN4_EXTRACT_SOURCE(msg) 		((msg & 0x000007E0) >> 5)
//#define CAN4_EXTRACT_DATABUFFER(msg)	((msg & 0xFFFFF800) >> 11)

//#define CAN4_PUT_PORT(port)				((uint32_t)port)
//#define CAN4_PUT_SOURCE(src)			((uint32_t)src)  << 5
//#define CAN4_PUT_DATABUFFER(buf)		((uint32_t)buf)	 << 11

uint8_t can4_ports[32];
uint8_t can4_msgbuffer[CAN4_BUF_MSG_COUNT][3]; //0 = Source, 1 = Port, 2 = Databuffer
uint8_t can4_databuffer[CAN4_BUF_DATA_COUNT];
uint8_t can4_bytebuffer[CAN4_BUF_DATA_COUNT][8];


static void can4_adaptRef(uint8_t dbuf, uint8_t databuf);
static uint8_t can4_getFreeMsgBuffer(void);
static uint8_t can4_getMsgBuffer(uint8_t port, uint8_t source);
static uint8_t can4_getFreeDataBuffer(void);
static void can4_saveDataToByteBuffer(uint8_t databuf, uint8_t* data);
static uint8_t can4_saveCompleteData(uint8_t databuf, uint8_t* data, uint8_t offset, uint8_t len);

uint8_t can4_init(uint8_t address) {
	uint8_t i;

	//Reset all port values
	for(i = 0; i <= CAN4_MAX_PORT; i++)
		can4_ports[i] = 0;

	for(i = 0; i < CAN4_BUF_MSG_COUNT; i++)
		can4_msgbuffer[i][0] = CAN4_BUF_MSG_UNUSED;

	for(i = 0; i < CAN4_BUF_DATA_COUNT; i++)
		can4_databuffer[i] = CAN4_BUF_UNUSED;

	return can3_init(address);
}

uint8_t can4_open(uint8_t port) {
	uint8_t tmp;

	//Return 0 if port >= 32
	CAN4_RETURN_UBOUNDS(port,CAN4_MAX_PORT,0);

	//Return 0 if port is already open
	if(can4_ports[port]) return 0;

	tmp = can3_maskedOpen(_PV(port),0x003E);

	if(tmp == 0) return 0;

	can4_ports[port] = tmp;

	return 1;
}

uint8_t can4_send(uint8_t dest, uint8_t port, uint8_t* data, uint8_t len, uint8_t interrupt) {
	uint8_t i = 0, n = 0, m = 0;
	uint8_t msg[8];
	uint8_t count;

	//CALC HEADER DATA
	count = len / 8;

	if(len % 8)
		count += 1;

	//SEND REST OF MESSAGE
	for(i = 0; i < len; ) {
		while(n < 8 && i < len) {
			msg[n] = data[i];
			n++; i++;
		}

		if(!can3_send(dest,_PV(port) | _NV(m) | _CV(count), msg, n, interrupt)) return 0;
		n = 0; m++;
	}

	return 1;
}

uint8_t can4_getData(uint8_t port, uint8_t* data, uint8_t* src) {
	//Init Vars
	uint16_t _id;
	uint8_t _count;
	uint8_t _num;
	uint8_t _len;
	uint8_t _src;
	uint8_t _data[8];
	uint8_t msgbuf;
	uint8_t databuf;

	//Return 0 if port >= 32
	CAN4_RETURN_UBOUNDS(port,CAN4_MAX_PORT,0);

	//Return 0 if port is not open
	if(!can4_ports[port]) return 0;

	//Get MSG
	_len = can3_getData(can4_ports[port],_data,&_src,&_id);

	if(_len == 0)	return 0; //Nothing to do

	//Get MSG header
	_count = CAN4_EXTRACT_COUNT(_id);
	_num   = CAN4_EXTRACT_NUMBER(_id);

	//single message
	if(_count == 1) {
		uint8_t i;
		for(i = 0; i < _len; i++)
			data[i] = _data[i];

		*src = _src;
		return _len;
	}

	/*
	 * Multiple Messages
	 */

	//get free msgbuffer
	msgbuf = ((_num == 0) ? can4_getFreeMsgBuffer() : can4_getMsgBuffer(port,_src));
	if(msgbuf == 0)	return 0; //Msgbuffer overflow

	//get free databuffer
	databuf = can4_getFreeDataBuffer();
	if(databuf == 0) return 0; //Databuffer overflow

	//index correction
	msgbuf--;
	databuf--;

	//save msg data
	can4_databuffer[databuf] = CAN4_BUF_EOM;
	can4_saveDataToByteBuffer(databuf, _data);

	if(_num == 0) { //save msg header
		//can4_msgbuffer[msgbuf] = CAN4_PUT_PORT(port) | CAN4_PUT_SOURCE(_src) | CAN4_PUT_DATABUFFER(databuf);
		can4_msgbuffer[msgbuf][0] = _src;
		can4_msgbuffer[msgbuf][1] = port;
		can4_msgbuffer[msgbuf][2] = databuf;
		return 0;
	}

	//adapt reference
	can4_adaptRef(can4_msgbuffer[msgbuf][2],databuf);

	//check if msg is complete
	if(_num == (_count - 1)) { //msg complete
		*src = _src;
		_len = can4_saveCompleteData(can4_msgbuffer[msgbuf][2],data, 0,0);

		//free space
		can4_msgbuffer[msgbuf][0] = CAN4_BUF_MSG_UNUSED;

		return _len;
	}

	//sry still not complete
	return 0;
}

static uint8_t can4_saveCompleteData(uint8_t databuf, uint8_t* data, uint8_t offset, uint8_t len) {
	uint8_t i;
	uint8_t _len;

	for(i = 0; i < 8; i++) {
		data[offset * 8 + i] = can4_bytebuffer[databuf][i];
	}

	if(can4_databuffer[databuf] != CAN4_BUF_EOM)
		_len = can4_saveCompleteData(can4_databuffer[databuf], data, offset + 1, len + 8);
	else
		_len = (len + 8);

	//free space
	can4_databuffer[databuf] = CAN4_BUF_UNUSED;
	return _len;
}

static void can4_adaptRef(uint8_t dbuf, uint8_t databuf) {
	if(can4_databuffer[dbuf] == CAN4_BUF_EOM)
		can4_databuffer[dbuf] = databuf;
	else
		can4_adaptRef(can4_databuffer[dbuf],databuf);
}

static uint8_t can4_getMsgBuffer(uint8_t port, uint8_t source) {
	uint8_t i;

	for(i = 1; i <= CAN4_BUF_MSG_COUNT; i++) {
		if(can4_msgbuffer[i - 1][0] == source &&
		   can4_msgbuffer[i - 1][1] == port) {
			return i;
		}
	}

	return 0;
}

static uint8_t can4_getFreeMsgBuffer(void) {
	uint8_t i;
	for(i = 1; i <= CAN4_BUF_MSG_COUNT; i++)  {
		if(can4_msgbuffer[i-1][0] == CAN4_BUF_MSG_UNUSED) {
			return i;
		}
	}

	return 0;
}

static uint8_t can4_getFreeDataBuffer(void) {
	uint8_t i;
	for(i = 1; i <= CAN4_BUF_DATA_COUNT; i++)  {
		if(can4_databuffer[i-1] == CAN4_BUF_UNUSED) {
			return i;
		}
	}

	return 0;
}

static void can4_saveDataToByteBuffer(uint8_t databuf, uint8_t* data) {
	uint8_t i;

	for(i = 0; i < 8; i++)
		can4_bytebuffer[databuf][i] = data[i];
}

void can4_close(uint8_t port) {
	if(can4_ports[port]) {
		can3_close(can4_ports[port]);
		can4_ports[port] = 0;
	}
}

#endif /* CAN4_C_ */
