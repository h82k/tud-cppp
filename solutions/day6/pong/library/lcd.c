/*! \file lcd.c */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 09.04.2009
// Revised		: 29.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//*****************************************************************************

#include "mb96348hs.h"
#include "lcd.h"
#include "lcd.cfg.h"
#include "util.h"
#include "font.h"

#if LCD_FRAMEBUFFER_MODE==1
static uint8_t lcd_buffer[128][8];
#endif

static uint8_t setEnable(void) {
	uint8_t data;
	delay_us(1);
	LCD_CTRL_PORT |= _BV(LCD_CTRL_E);
	delay_us(1);
	data = LCD_DATA_PORT;
	LCD_CTRL_PORT &= ~_BV(LCD_CTRL_E);
	delay_us(1);
	return data;
}

static void selectDisplay(uint8_t disp) {
	LCD_CTRL_PORT &= ~(_BV(LCD_CTRL_CS1) | _BV(LCD_CTRL_CS2));
	if (disp)
		LCD_CTRL_PORT |= _BV(LCD_CTRL_CS2);
	else
		LCD_CTRL_PORT |= _BV(LCD_CTRL_CS1);
}

static void setReadWrite(uint8_t write) {
	if (write) {
		LCD_DATA_PORT = 0x00;
		LCD_DATA_PIER = 0x00;
		LCD_DATA_DDR = 0xff;
		LCD_CTRL_PORT &= ~_BV(LCD_CTRL_RW);
	} else {
		LCD_DATA_PORT = 0x00;
		LCD_DATA_PIER = 0xff;
		LCD_DATA_DDR = 0x00;
		LCD_CTRL_PORT |= _BV(LCD_CTRL_RW);
	}
}

static void writeCommand(uint8_t cmd, uint8_t disp) {
	setReadWrite(1);
	selectDisplay(disp);
	LCD_CTRL_PORT &= ~_BV(LCD_CTRL_DI);
	LCD_DATA_PORT = cmd;
	setEnable();
}

static uint8_t readCommand(uint8_t disp) {
	setReadWrite(0);
	selectDisplay(disp);
	LCD_CTRL_PORT &= ~_BV(LCD_CTRL_DI);
	return setEnable();
}

static void writeData(uint8_t data, uint8_t disp) {
	setReadWrite(1);
	selectDisplay(disp);
	LCD_CTRL_PORT |= _BV(LCD_CTRL_DI);
	LCD_DATA_PORT = data;
	setEnable();
}

static uint8_t readData(uint8_t disp) {
	uint8_t data;
	setReadWrite(0);
	selectDisplay(disp);
	LCD_CTRL_PORT |= _BV(LCD_CTRL_DI);
	setEnable();
	data = setEnable();
	return data;
}

static uint8_t setXY(uint8_t x, uint8_t y) {
	uint8_t moduleX = x % 64;
	uint8_t disp = x / 64;
	uint8_t page = y / 8;
	writeCommand(LCD_CMD_SETADDRESS | moduleX, disp);
	writeCommand(LCD_CMD_SETPAGE | page, disp);
	return disp;
}

void lcd_init(void) {
	LCD_CTRL_PORT = 0x00;
	LCD_CTRL_DDR = 0xff;
	LCD_CTRL_PORT |= _BV(LCD_CTRL_RESET);
	writeCommand(LCD_CMD_ON, 0);
	writeCommand(LCD_CMD_ON, 1);
	lcd_clear(0);
	writeCommand(LCD_CMD_STARTLINE | 0, 0);
	writeCommand(LCD_CMD_STARTLINE | 0, 1);
}

void lcd_clear(uint8_t color) {
	uint8_t x;
	uint8_t y;

	for (y = 0; y < 8; y++) {
#if LCD_FRAMEBUFFER_MODE == 1
		for (x = 0; x < 128; x++) {
			lcd_buffer[x][y] = (color ? 0xff : 0x00);
		}
#else
		setXY(0, y*8);
		for (x= 0; x < 64; x++)
			writeData((color ? 0xff : 0x00), 0);
		setXY(64, y*8);
		for (x= 0; x < 64; x++)
			writeData((color ? 0xff : 0x00), 1);
#endif
	}
}

void lcd_drawPage(uint8_t x, uint8_t page, uint8_t data) {
#if LCD_FRAMEBUFFER_MODE==0
	uint8_t disp;
#endif
	if ((page > 7) || (x > 127))
		return;
#if LCD_FRAMEBUFFER_MODE==1
	lcd_buffer[x][page] = data;
#else
	disp = setXY(x, page * 8);
	writeData(data, disp);
#endif
}

void lcd_drawPixel(int16_t x, int16_t y, uint8_t color) {
#if LCD_FRAMEBUFFER_MODE==1
	if ((x > 127) || (y > 63) || (x < 0) || (y < 0))
		return;

	if (color)
		lcd_buffer[x][y / 8] |= (1 << (y % 8));
	else
		lcd_buffer[x][y / 8] &= ~(1 << (y % 8));
#else
	uint8_t data;
	uint8_t disp;
	if ((x > 127) || (y > 63) || (x < 0) || (y < 0))
		return;

	disp = setXY(x, y);
	data = readData(disp);
	if (color)
	data |= (1 << (y % 8));
	else
	data &= ~(1 << (y % 8));

	setXY(x, y);
	writeData(data, disp);
#endif
}

int8_t lcd_getPixel(int16_t x, int16_t y)
{
#if LCD_FRAMEBUFFER_MODE==1
	if ((x > 127) || (y > 63) || (x < 0) || (y < 0))
		return -1;
	return (lcd_buffer[x][y / 8] >> (y % 8)) & 0x01;
#else
	uint8_t disp;
	if ((x > 127) || (y > 63) || (x < 0) || (y < 0))
		return -1;
	disp = setXY(x, y);
	return (readData(disp) >> (y % 8)) & 0x01;
#endif
}

void lcd_drawCircle(int16_t x, int16_t y, uint8_t r, uint8_t black, uint8_t filled) {
	/*
	 * Berechnung nach Bresenham
	 * http://de.wikipedia.org/wiki/Bresenham-Algorithmus#Kreisvariante_des_Algorithmus
	 */
	int16_t f = 1 - r;
	int16_t ddF_x = 0;
	int16_t ddF_y = -2 * r;
	int16_t ix = 0;
	int16_t iy = r;

	if (filled) {
		lcd_drawRect(x, y - r, 1, 2 * r, black, 1);
	} else {
		lcd_drawPixel(x, y + r, black);
		lcd_drawPixel(x, y - r, black);
		lcd_drawPixel(x + r, y, black);
		lcd_drawPixel(x - r, y, black);
	}

	while (ix < iy) {
		if (f >= 0) {
			iy--;
			ddF_y += 2;
			f += ddF_y;
		}
		ix++;
		ddF_x += 2;
		f += ddF_x + 1;

		if (filled) {
			lcd_drawRect(x - ix, y - iy, 1, 2 * iy, black, 1);
			lcd_drawRect(x + ix, y - iy, 1, 2 * iy, black, 1);
			lcd_drawRect(x - iy, y - ix, 1, 2 * ix, black, 1);
			lcd_drawRect(x + iy, y - ix, 1, 2 * ix, black, 1);
		} else {
			lcd_drawPixel(x + ix, y + iy, black);
			lcd_drawPixel(x - ix, y + iy, black);
			lcd_drawPixel(x + ix, y - iy, black);
			lcd_drawPixel(x - ix, y - iy, black);
			lcd_drawPixel(x + iy, y + ix, black);
			lcd_drawPixel(x - iy, y + ix, black);
			lcd_drawPixel(x + iy, y - ix, black);
			lcd_drawPixel(x - iy, y - ix, black);
		}
	}
}

void lcd_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t black, uint8_t filled) {
	uint8_t startPage, endPage, pages;
	uint8_t ix, iPage;

	if (!filled) {
		lcd_drawLine(x,     y, x+w,   y, black);
		lcd_drawLine(x+w,   y, x+w, y+h, black);
		lcd_drawLine(x+w, y+h,   x, y+h, black);
		lcd_drawLine(x,   y+h,   x,   y, black);
		return;
	}

	if ((x > 127) || (y > 63) || (x+w < 0) || (y+h < 0))
		return;

	if (x+w > 128)	w = 128-x;
	if (y+h >  64)	h =  64-y;
	if (x < 0) {w+=x; x=0;}
	if (y < 0) {h+=y; y=0;}

	startPage = y / 8;
	endPage = (y + h - 1) / 8;
	pages = endPage - startPage + 1;

	for (iPage = startPage; iPage < endPage + 1; iPage++) {
		uint8_t data, curData;
		if (iPage == startPage) {
			if (pages > 1)
				data = 0xff << (y - startPage * 8);
			else
				data = (0xff >> (8 - h)) << (y - startPage * 8);
		} else if (iPage == endPage) {
			data = 0xff >> (7 - (y + h - 1) % 8);
		} else {
			data = 0xff;
		}
		for (ix = x; ix < (x + w); ix++) {
#if LCD_FRAMEBUFFER_MODE == 1
			if (data == 0xff) {
				if (black)
					curData = data;
				else
					curData = ~data;
			} else {
				curData = lcd_buffer[x][iPage];
				if (black)
					curData |= data;
				else
					curData &= ~data;
			}
			lcd_buffer[x][iPage] = curData;
#else
			uint8_t disp = setXY(ix, iPage * 8);
			if (data == 0xff) {
				if (black)
				curData = data;
				else
				curData = ~data;
			} else {
				curData = readData(disp);
				if (black)
				curData |= data;
				else
				curData &= ~data;
				setXY(ix, iPage * 8);
			}
			writeData(curData, disp);
#endif
		}
	}
}

void lcd_drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t black) {
	/*
	 * Berechnung nach Bresenham
	 * http://de.wikipedia.org/wiki/Bresenham-Algorithmus#C-Implementierung
	 */
	int16_t x, y, t, dx, dy, incx, incy, pdx, pdy, ddx, ddy, es, el, err;

	/* Entfernung in beiden Dimensionen berechnen */
	dx = x2 - x1;
	dy = y2 - y1;

	/* Vorzeichen des Inkrements bestimmen */
	incx = sgn(dx);
	incy = sgn(dy);

	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;

	/* feststellen, welche Entfernung größer ist */
	if (dx > dy) {
		/* x ist schnelle Richtung */
		pdx = incx;
		pdy = 0; /* pd. ist Parallelschritt */

		ddx = incx;
		ddy = incy; /* dd. ist Diagonalschritt */

		es = dy;
		el = dx; /* Fehlerschritte schnell, langsam */
	} else {
		/* y ist schnelle Richtung */
		pdx = 0;
		pdy = incy; /* pd. ist Parallelschritt */

		ddx = incx;
		ddy = incy; /* dd. ist Diagonalschritt */

		es = dx;
		el = dy; /* Fehlerschritte schnell, langsam */
	}

	/* Initialisierungen vor Schleifenbeginn */
	x = x1;
	y = y1;
	err = el / 2;

	lcd_drawPixel(x, y, black);

	/* Pixel berechnen */
	for (t = 0; t < el; t++) { /* t zaehlt die Pixel, el ist auch Anzahl */
		/* Aktualisierung Fehlerterm */
		err -= es;
		if (err < 0) {
			/* Fehlerterm wieder positiv (>=0) machen */
			err += el;

			/* Schritt in langsame Richtung, Diagonalschritt */
			x += ddx;
			y += ddy;
		} else {
			/* Schritt in schnelle Richtung, Parallelschritt */
			x += pdx;
			y += pdy;
		}
		lcd_drawPixel(x, y, black);
	}
}

uint8_t lcd_drawCharacter(uint8_t x, uint8_t page, char ascii,
		uint8_t black, uint8_t overlay) {
	uint8_t* pages;
	uint8_t i;

	if ((x > 127) || (page > 7) || (ascii > 127))
		return 0;

	pages = font_getChar(ascii, FONT_REGULAR);

	if (pages != 0) {
		for (i = 0; i < 5; i++) {
#if LCD_FRAMEBUFFER_MODE == 1
			uint8_t curData = (black ? 0 : 255);
			if (overlay)
				curData = lcd_buffer[x][page];

			if (black)
				curData |= *pages++;
			else
				curData &= ~(*pages++);
			lcd_buffer[x][page] = curData;
#else
			uint8_t disp = setXY(x, page * 8);
			uint8_t curData = (black ? 0 : 255);
			if (overlay)
				curData = readData(disp);

			if (black)
				curData |= *pages++;
			else
				curData &= ~(*pages++);
			setXY(x, page * 8);
			writeData(curData, disp);
#endif
			x++;
		}
		return ++x;
	}
	return x;
}

uint8_t lcd_drawString(uint8_t x1, uint8_t page1, uint8_t x2, uint8_t page2,
		uint8_t wrap, uint16_t delay, char* firstChar, uint8_t black,
		uint8_t overlay) {
	uint8_t curX = x1;
	uint8_t curPage = page1;
	char curChar = 0;

	if ((x1 > 127) || (page1 > 7) || (x2 > 128) || (page2 > 8))
		return 0;

	if (x2)
		if ((x2 - x1) < 5)
			return x1;

	for (curChar = *firstChar++; curChar != 0; curChar = *firstChar++) {
		if (curChar == '\n') {
			if (!wrap)
				return curX;
			curX = x1;
			curPage++;
			if (curPage)
				if (curPage > page2)
					return curX;
		}
		curX = lcd_drawCharacter(curX, curPage, curChar, black, overlay);
		if (x2) {
			if ((curX + 5) > x2) {
				if (!wrap)
					return curX;
				curX = x1;
				curPage++;
				if (curPage > page2)
					return curX;
			}
		}
		delay_ms(delay);
	}
	return curX;
}

int16_t lcd_drawCharacterPrecise(int16_t x, int16_t y, char ascii, uint8_t black, uint8_t orientation, uint8_t font) {
	uint8_t* pages;
	uint8_t i, j;
	uint8_t fontwidth = font_getWidth(font);
	uint8_t fontheight = font_getHeight(font);
	uint8_t offset = (8-fontheight);

	pages = font_getChar(ascii, font);

	if (pages == 0) {
		if (orientation & (LCD_ORIENTATION_90 | LCD_ORIENTATION_270)) {
			return y;
		} else {
			return x;
		}
	}
	if (orientation & LCD_ORIENTATION_90) {
		for (i = 0; i < fontwidth; i++) {
			for (j = 0; j < fontheight; j++) {
				if (pages[i] & 1<<(j+offset)) {
					lcd_drawPixel(x-j, y, black);
				}
			}
			y++;
		}
		return ++y;
	} else if (orientation & LCD_ORIENTATION_180) {
		for (i = 0; i < fontwidth; i++) {
			for (j = 0; j < fontheight; j++) {
				if (pages[i] & 1<<(j+offset)) {
					lcd_drawPixel(x, y-j, black);
				}
			}
			x--;
		}
		return --x;
	} else if (orientation & LCD_ORIENTATION_270) {
		for (i = 0; i < fontwidth; i++) {
			for (j = 0; j < fontheight; j++) {
				if (pages[i] & 1<<(j+offset)) {
					lcd_drawPixel(x+j, y, black);
				}
			}
			y--;
		}
		return --y;
	} else { // 0 deg = default
		for (i = 0; i < fontwidth; i++) {
			for (j = 0; j < fontheight; j++) {
				if (pages[i] & 1<<(j+8-fontheight)) {
					lcd_drawPixel(x, y+j, black);
				}
			}
			x++;
		}
		return ++x;
	}
}


int16_t lcd_drawStringPrecise(int16_t x, int16_t y, char* firstChar, uint8_t black, uint8_t settings, uint8_t font) {
	int width;
	int height;
	int len = 0;
	while (firstChar[len++] != 0);
	len--;

	width = (len*font_getWidth(font));
	height = font_getHeight(font);

	// calculate offset
	if (settings & LCD_ORIENTATION_90)
	{
		if (settings & LCD_ALIGNMENT_CENTER) {
			y -= width>>1;
		} else if (settings & LCD_ALIGNMENT_RIGHT) {
			y -= width;
		}
		if (settings & LCD_ALIGNMENT_MIDDLE) {
			x += height>> 1;
		} else if (settings & LCD_ALIGNMENT_BOTTOM) {
			x += height;
		}
	}
	else if (settings & LCD_ORIENTATION_180)
	{
		if (settings & LCD_ALIGNMENT_CENTER) {
			x += width>>1;
		} else if (settings & LCD_ALIGNMENT_RIGHT) {
			x += width;
		}
		if (settings & LCD_ALIGNMENT_MIDDLE) {
			y += height>> 1;
		} else if (settings & LCD_ALIGNMENT_BOTTOM) {
			y += height;
		}
	}
	else if (settings & LCD_ORIENTATION_270)
	{
		if (settings & LCD_ALIGNMENT_CENTER) {
			y += width>>1;
		} else if (settings & LCD_ALIGNMENT_RIGHT) {
			y += width;
		}
		if (settings & LCD_ALIGNMENT_MIDDLE) {
			x -= height>> 1;
		} else if (settings & LCD_ALIGNMENT_BOTTOM) {
			x -= height;
		}
	}
	else
	{
		if (settings & LCD_ALIGNMENT_CENTER) {
			x -= width>>1;
		} else if (settings & LCD_ALIGNMENT_RIGHT) {
			x -= width;
		}
		if (settings & LCD_ALIGNMENT_MIDDLE) {
			y -= height>> 1;
		} else if (settings & LCD_ALIGNMENT_BOTTOM) {
			y -= height;
		}
	}


	// draw characters
	if (settings & (LCD_ORIENTATION_90 | LCD_ORIENTATION_270)) {
		while (*firstChar != 0) {
			y = lcd_drawCharacterPrecise(x, y, *firstChar, black, settings, font);
			firstChar++;
		}
		return y;
	} else {
		while (*firstChar != 0) {
			x = lcd_drawCharacterPrecise(x, y, *firstChar, black, settings, font);
			firstChar++;
		}
		return x;
	}
}

void lcd_flush(void) {
#if LCD_FRAMEBUFFER_MODE==1
	uint8_t disp, x, page;
	for (disp = 0; disp < 2; disp++) {
		for (page = 0; page < 8; page++) {
			writeCommand(LCD_CMD_SETPAGE | page, disp);
			writeCommand(LCD_CMD_SETADDRESS | 0, disp);
			for (x = 0; x < 64; x++) {
				writeData(lcd_buffer[x+64*disp][page], disp);
			}
		}
	}
#endif
}
