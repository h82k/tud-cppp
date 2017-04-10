/**
 * Author: Ludwig Meysel
 * Created: 24.09.2015
 */

#include "mb96348hs.h"
#include "lcd.h"
#include "adc.h"
#include <stdio.h>

short player = 1;
short fields[3][3];
short pushes = 0;
short d1 = 0, d2 = 0;

// definitions to increase readability
#define BUTTON_LEFT  PDR07_P0
#define BUTTON_RIGHT PDR07_P1

// initialize I/O-ports
void initIO(void) {
	PDR00 = 0xff;
	DDR00 = 0xff;		// set port00 as output (right seven-segment display)
	PDR09 = 0xff;
	DDR09 = 0xff;		// set port09 as output (left seven-segment display)
	PDR07 = 0x00;
	DDR07 = 0xfc;		// set P07_0 and P07_1 as input (buttons) - 0xfc = 11111100 (bin)
	PIER07 = 0x03;		// enable input - 0x03 = 00000011 (bin)
}

void drawField(void) {
	lcd_drawLine(32, 21, 95, 21, 1);
	lcd_drawLine(32, 42, 95, 42, 1);
	lcd_drawLine(53, 0, 53, 63, 1);
	lcd_drawLine(74, 0, 74, 63, 1);
}
void drawMarker(short x, short y, int black) {
	char xOff = 21 * x + 43, yOff = 21 * y + 10;
	lcd_drawRect(xOff - 1, yOff - 1, 3, 3, black, 1);
}
void wait(long cyc) {
	long d;
	for (d = 0; d < cyc; d++) {
		__wait_nop();
	}
}
void placePlayerMark(short x, short y, short player) {
	char xOff = 21 * x + 43, yOff = 21 * y + 10;
	fields[x][y] = player;
	if (player == 1) {
		lcd_drawLine(xOff - 5, yOff - 5, xOff + 5, yOff + 5, 1);
		lcd_drawLine(xOff - 5, yOff + 5, xOff + 5, yOff - 5, 1);
	}
	if (player == 2) {
		lcd_drawCircle(xOff, yOff, 5, 1, 0);
	}
}

int checkStatus(short x, short y) {
	int i, h = 1, v = 1;
	for (i = 0; i < 3; i++)
		if (fields[i][y] != player) {
			v = 0;
			break;
		}
	if (v) {
		return 1;
	}
	for (i = 0; i < 3; i++)
		if (fields[x][i] != player) {
			h = 0;
			break;
		}
	if (h) {
		return 1;
	}
	if (fields[0][0] == player && fields[1][1] == player && fields[2][2] == player) {
		return 1;
	}
	if (fields[2][0] == player && fields[1][1] == player && fields[0][2] == player) {
		return 1;
	}
	return 0;
}

void main(void) {
	short mx, my, tmx, tmy, ignoreBtn;
	char stat[14];
	// TODO initialise variables with the riht value
	//mx = -1;
	//my = -1;
	//ignoreBtn = 0;
	
	lcd_init();
	initIO();
	adc_init();
	
	lcd_clear(0);
	drawField();
	
	for (;;) {
		tmx = (short) (2 - adc_getValue(1) / 255.0 * 2 + 0.5);
		tmy = (short) (2 - adc_getValue(2) / 255.0 * 2 + 0.5);
		if (tmy != my || tmx != mx) {
			drawMarker(mx, my, 0);
			if (fields[mx][my] == 1) {
				placePlayerMark(mx, my, 1);
			}
			drawMarker(mx = tmx, my = tmy, 1);
		}
		if (!BUTTON_RIGHT && !ignoreBtn && !fields[mx][my]) {
			ignoreBtn = 1;
			pushes++;
			placePlayerMark(mx, my, player);
			if (checkStatus(mx, my)) {
				lcd_clear(0);
				sprintf(stat, "Player %u won!", player);
				lcd_drawString(27, 4, 0, 4, 0, 0, &stat[0], 1, 1);
				lcd_flush();
				break;
			}
			if (pushes == 9) {
				lcd_clear(0);
				sprintf(stat, "Undecided!");
				lcd_drawString(32, 4, 0, 4, 0, 0, &stat[0], 1, 1);
				lcd_flush();
				break;
			}
			if (player == 1) {
				player = 2;
			}
			else if (player == 2) {
				player = 1;
			}
		} else if (BUTTON_RIGHT && ignoreBtn) {
			ignoreBtn = 0;
		}
	}
}
