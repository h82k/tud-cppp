/**
 * Author: Matthias Gazzari
 * Created: 23.09.2015
 */

#include "mb96348hs.h"
#include "16FXlib/lcd.h"
#include "16FXlib/adc.h"
#include "16FXlib/seg.h"
#include "16FXlib/buttons.h"

/// number of different ADC values
#define ADC_COUNT 256

/**
 * Escape time algorithm to determine whether the complex number x0 + i * y0 is in the
 * Mandelbrot set calcuating the escape time. Values outside of the Mandelbrot set will
 * escape quickly, values close to the Mandelbrot set will escape very slowly and values
 * inside the Mandelbrot set will never escape.
 * @param x0		- the real part - must be in (-2.5, 1)
 * @param y0		- the imaginary part - must be in (-1, 1)
 * @param iteration	- maximum number of iterations (aka maximum escape time)
 * @return			- number of iterations (aka escape time)
 */
int mandelbrotSet(float x0, float y0, int iteration) {
	float xTemp;
	float x = 0.0f;
	float y = 0.0f;
	int k = 0;
	// determine the escape time of the given complex number
	// complex numbers with an absolute value of 2 or greater can not be in the Mandelbrot set
	while ((k < iteration) && (x * x + y * y < 2 * 2)) {
		xTemp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = xTemp;
		++k;
	}
	return k;
}

/**
 * Draw the Mandelbrot set onto the lcd using the escape time algorithm.
 * @param scale		- scale applied to the complex interval drawn
 * @param xOffset	- horizontal offset applied to the complex interval drawn
 * @param yOffset	- vertical offset applied to the complex interval drawn
 * @param iteration - maximum number of iterations (aka maximum escape time)
 * @param threshold - threshold escape time to determine whether a point is in the set or not
 */
void drawMandelbrotSet(int scale, int xOffset, int yOffset, int iteration, int threshold) {
	int i, j;
	float x0, y0;
	float xMin = -2.5f / scale;
	float xMax = 1.0f / scale;
	float yMin = -1.0f / scale;
	float yMax = 1.0f / scale;
	for (i = 0; i < LCD_WIDTH; ++i) {
		for (j = 0; j < LCD_HEIGHT; ++j) {
			// apply horizontal offset and convert to the interval (xMin, xMax)
			x0 = (i + xOffset) * (xMax - xMin) / LCD_WIDTH + xMin;
			// apply vertical offset and convert to the interval (yMin, yMax)
			y0 = (j + yOffset) * (yMax - yMin) / LCD_HEIGHT + yMin;
			// evaluate wheter the given complex number x0 + i * y0 is in the Mandelbrot set or not
			if (threshold > mandelbrotSet(x0, y0, iteration)) {
				lcd_drawPixel(i, j, LCD_COLOR_BLACK);
			}
			else {
				lcd_drawPixel(i, j, LCD_COLOR_WHITE);
			}
		}
	}
}

/**
 * Convert an analog slider value to move the shown screen by two screen sizes
 * @param offset		- analog value to be converted
 * @param scale			- current scale of the interval displayed
 * @param horizontal	- whether the offset is horizontal or vertical
 * @return				- the transformed offset value
 */
int convert(int value, int scale, int horizontal) {
	value -= ADC_COUNT / 2;
	value *= (horizontal) ? LCD_WIDTH : LCD_HEIGHT;
	value *= 2;
	value *= scale;
	value /= ADC_COUNT;
	return value;
}

/**
 * Draw the Mandelbrot set with a given zoom level (
 * Show current zoom level on the seven segment display.
 */
void main(void) {
	// variable declaration
	int xOffset, yOffset, zoomLevel, dirtyBit;
	
	// initialise lcd, adc and buttons
	seg_init();
	buttons_init();
	lcd_init();
	adc_init();
	
	// initialise variables
	zoomLevel = 0;
	xOffset = adc_getValue(1);
	yOffset = adc_getValue(2);
	dirtyBit = 1;
	
	while(1) {
		// change zoom level with the buttons
		if (buttons_get(0)) {
			dirtyBit = 1;
			if (zoomLevel > 0) {
				--zoomLevel;
			}
			else {
				zoomLevel = 99;
			}
		}
		if (buttons_get(1)) {
			dirtyBit = 1;
			if (zoomLevel < 99) {
				++zoomLevel;
			}
			else {
				zoomLevel = 0;
			}
		}
		
		// show the current zoom level on the seven segment display
		seg_num(zoomLevel);
		
		// change offset with the analog sliders
		if (adc_getValue(1) < xOffset - 1 || adc_getValue(1) > xOffset + 1) {
			dirtyBit = 1;
			xOffset = adc_getValue(1);
		}
		if (adc_getValue(2) < yOffset - 1 || adc_getValue(2) > yOffset + 1) {
			dirtyBit = 1;
			yOffset = adc_getValue(2);
		}
		
		// draw the Mandelbrot set onto the lcd if the zoom level or offsets were changed
		if (dirtyBit) {
			lcd_clear(LCD_COLOR_BLACK);
			drawMandelbrotSet(
				zoomLevel + 1,							// scale
				convert(xOffset, zoomLevel + 1, 1),		// xOffset
				convert(yOffset, zoomLevel + 1, 0),		// yOffset
				17,										// iterations (escape time)
				17										// threshold (black or white pixel)
			);
			dirtyBit = 0;
		}
		delay_ms(100);
	}
	
}
