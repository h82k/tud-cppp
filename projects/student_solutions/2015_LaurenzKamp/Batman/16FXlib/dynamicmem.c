/*! \file dynamicmem.c */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 18.09.2009
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
