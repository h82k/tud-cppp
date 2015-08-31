#include "mb96348hs.h"
#include "16FXlib/util.h"
#include "16FXlib/lcd.h"
#include "16FXlib/adc.h"

const char DEC7SEG[10] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
		0x80, 0x90 };
const uint8_t size = 3;
const uint8_t bumpsize = 8;
const uint8_t move = 2;

#define ANZ 48

uint8_t checkCollision(uint8_t x, uint8_t y)
{
	if(y > 0)
		if(lcd_getPixel(x + size / 2, y - 1))
		{
			PDR09 = DEC7SEG[1];
			return 1;
		}
	if(x > 0)
		if(lcd_getPixel(x - 1, y + size / 2))
		{
			PDR09 = DEC7SEG[2];
			return 1;
		}
	if(y < 64 - size)
		if(lcd_getPixel(x + size / 2, y + size))
		{
			PDR09 = DEC7SEG[3];
			//lcd_drawRect(x + size / 2, y + size, 1, 1, 1);
			return 1;
		}
	if(x < 128 - size)
		if(lcd_getPixel(x + size, y + size / 2))
		{
			PDR09 = DEC7SEG[4];
			return 1;
		}
	return 0;
}

void blinken(char *text)
{
	delay_ms(500);
	lcd_clear(0);
	lcd_drawString(48, 4, 48 + 36, 16, 0, 0, text, 1, 0);
	delay_ms(500);
	lcd_clear(1);
	lcd_drawString(48, 4, 48 + 36, 16, 0, 0, text, 0, 0);
}

void winner(void)
{
	char *winnertext = "winner";
	lcd_clear(0);
	for(;;)
		blinken(winnertext);
}

void looser(void)
{
	char *loosertext = "looser";
	lcd_clear(1);
	for(;;)
		blinken(loosertext);
}

uint8_t bumpcollision(uint8_t bumpx[], uint8_t bumpy[], uint8_t checklimit, uint8_t genx, uint8_t geny)
{
	uint8_t i = 0;
	for(i = 0; i < checklimit; i++)
	{
		if(bumpx[i] == genx && bumpy[i] == geny)
			return 1;
	}
	return 0;
}

uint8_t minmax(int number, uint8_t max)
{
	if(number < 0)
		return 0;
	if(number > max - size)
		return max - size;
	return number;
}

int posorneg(void)
{
	return random() % 2 ? 1 : -1;
}

void main(void) {


	uint8_t genx = 0;
	uint8_t geny = 0;
	int8_t posx = 0;
	int8_t posy = 0;
	uint8_t bumpx[ANZ + 1];
	uint8_t bumpy[ANZ + 1];
	uint8_t i = 0;
	uint8_t mscount = 0;
	int8_t randx = 0;
	int8_t randy = 0;
	//char *schtring = "hello world";
	PDR00 = 0xff;
	DDR00 = 0xff; // Set Port00 as output (right 7Segment display)
	PDR09 = 0xff;
	DDR09 = 0xff; // Set Port09 as output (left 7Segment display)


	PDR09 = DEC7SEG[1];
	PDR00 = DEC7SEG[1];

	lcd_init();
	adc_init();
	lcd_clear(0);
	random_init();

	for(i = 0; i < ANZ + 1; i++)
	{
		do
		{
			genx = (random() % (128 / bumpsize)) * bumpsize;
			geny = (random() % (64 / bumpsize)) * bumpsize;
		} while((genx == 0 && geny == 0) || bumpcollision(bumpx, bumpy, i, genx, geny));
		bumpx[i] = genx;
		bumpy[i] = geny;
	}
	for(;;)
	{
		for(i = 0; i < ANZ; i++)
		{
			lcd_drawRect(bumpx[i], bumpy[i], bumpsize, bumpsize, 1, 1);
		}
		lcd_drawRect(bumpx[ANZ], bumpy[ANZ], size + 2, size + 2, 0, 1);
		lcd_drawRect(posx, posy, size, size, 0, 1);
		posx = minmax((int) (((float) -(adc_getValue(1) - 255) / (float) 255) * (128 - size)) + randx, 128);
		posy = minmax((int) (((float) -(adc_getValue(2) - 255) / (float) 255) * (64 - size)) + randy, 64);
		lcd_drawRect(posx, posy, size, size, 1, 1);
		if(checkCollision(posx, posy) == 1)
			looser();
		if(posx == bumpx[ANZ] + 1 && posy == bumpy[ANZ] + 1)
			winner();
		lcd_drawRect(bumpx[ANZ], bumpy[ANZ], size + 2, size + 2, 1, 1);
		lcd_drawRect(bumpx[ANZ] + 1, bumpy[ANZ] + 1, size, size, 0, 1);
		mscount++;
		if(mscount == 50)
		{
			mscount = 0;
			if(random() % 2)
			{
				randx = minmax(randx + posorneg(), 5 + size);
			}
			else
			{
				randy = minmax(randy + posorneg(), 5 + size);

			}
		}
		delay_ms(10);
	}
}

