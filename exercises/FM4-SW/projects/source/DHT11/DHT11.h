#ifndef DHT11_H
#define DHT11_H

#include "mcu.h"
#include "pdl_header.h"
#include "analog.h"
#include "delay_rtc.h"
#include "gfx.h"

uint8_t data[5];

uint8_t readDHT11(uint8_t *feuchtigkeit, uint8_t *temperatur);
void rauminformationen();

#endif /* DHT11_H */