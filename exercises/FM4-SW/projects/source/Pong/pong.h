#ifndef PONG_H
#define PONG_H

#define PLAYER_L		1
#define PLAYER_R		2

#define MIN_X			1
#define MAX_X			480
#define MIN_Y			1
#define MAX_Y			320

#define PEDAL_WIDTH		10
#define PEDAL_HEIGHT	64
#define PEDAL_HEIGHT_S	16
#define PEDAL_SMALL_AFTER	15
#define PEDAL_SMALL_LENGTH	3

#define MAX_BALLS		1
#define NEW_BALL_BOUNCES	10

#include "mcu.h"
#include "pdl_header.h"
#include "analog.h"
#include "lcd.h"

struct position {
	uint16_t x;
	uint16_t y;
};

struct direction {
	int8_t x;
	int8_t y;
};

struct pong_state {
	unsigned long delay;

	int bounces;
	int last_ball_added;

	int add_ball_in;

	unsigned char running;
	unsigned char winner;

	uint16_t pos_pedal_l;
	uint16_t pos_pedal_r;
	unsigned char size_pedal_l;
	unsigned char size_pedal_r;
	unsigned char pedal_count_l;
	unsigned char pedal_count_r;
	int small_next;

	int num_balls;
  int sizeOfBall;

	struct position pos_ball[MAX_BALLS];
	struct direction dir_ball[MAX_BALLS];
};

static struct pong_state state;

void pong_init(void);
int pong_loop(void);

#endif /* PONG_H */

