/*! \file dynamicmem.c */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 18.09.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//*****************************************************************************

#include "dynamicmem.h"
#include "dynamicmem.cfg.h"
#include "inttypes.h"

static uint16_t brk_siz = 0;
static char _heap[HEAP_SIZE];

char* sbrk(int size) {
	if (brk_siz + size > HEAP_SIZE || brk_siz + size < 0)
		return ((char*) -1);
	brk_siz += size;
	return (_heap + brk_siz - size);
}
