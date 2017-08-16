#define BOXSIZE 40
#define PENRADIUS 3

#include <stdint.h>
#include "s6e2ccxj.h"
#include "pdl_header.h"
#include "analog.h"
#include "gfx.h"
#include "lcd.h"
#include "display.h"

uint16_t oldcolor, currentcolor; 

/**
 * Prints the x,y and z-value of the touchscreen on the display.
 */
void debugTouch();

/** 
 * Initializes the paint studio.
 */
void initPaintTouch();

/**
 * Loop of paintTouch.
 */
void loopPaintTouch();

/**
 *
 */
void paintTouch();
