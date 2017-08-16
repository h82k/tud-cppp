#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

/**
 * \brief Synchronous function that blocks for the given amount of micro seconds
 */
void microDelay(uint32_t timeInMicroseconds);

#endif