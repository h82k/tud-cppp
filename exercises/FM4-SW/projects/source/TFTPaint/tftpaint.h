#ifndef TFTPAINT_H
#define TFTPAINT_H

#define BOXSIZE 40
#define PENRADIUS 3

#include "mcu.h"
#include "pdl_header.h"
#include "lcd.h"

uint16_t oldcolor, currentcolor;

void initTFTPaint();
void loopTFTPaint();

#endif /* TFTPAINT_H */