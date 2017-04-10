#ifndef __INPUT_H__
#define __INPUT_H__

#include "mb96348hs.h"

#define BUTTON_LEFT  PDR07_P0
#define BUTTON_RIGHT PDR07_P1

void input_init(void);
void input_update(void);

int input_button_pressed(int index);
int input_button_down(int index);

float input_get_analog(int index);

#endif // __INPUT_H__