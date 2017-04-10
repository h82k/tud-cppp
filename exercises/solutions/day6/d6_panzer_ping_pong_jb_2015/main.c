/**
 * Author: Johannes Barthel
 * Created: 24.09.2015
 */

#include "mb96348hs.h"
#include "util.h"
#include "lcd.h"
#include "buttons.h"
#include "adc.h"
#include <math.h>

#define GRAVITY 0.1f
#define MAX_BALLS 100
#define BALL_RADIUS 2
#define FRAME_DURATION 5 // play mode
//#define FRAME_DURATION 400 // debug mode
#define CANNON_RADIUS 4
#define BARREL_LENGTH 7
#define BLACK 1
#define WHITE 0
#define M_PI 3.141592653589793238462643383279f
#define CANNON_SPEED .2;
#define BALL_INITIAL_SPEED 2.7
#define CHARGE_DIVIDER 5.0f
#define WALL_HEIGHT 8
#define WALL_X 63

// set this to 0 to disable rebound:
#define REBOUND_X 1
#define REBOUND_Y 1


typedef struct {
	float x;
	float y;
	float v_x;
	float v_y;
	int time;
	int active;
} Ball;

typedef struct {
	float x;
	float destination_x;
	float angle;
	float spawn_x;
} Cannon;

typedef struct {
	long charge;
	int pressed;
} Trigger;

Ball ballArr[MAX_BALLS];
Cannon cannonArr[2];
Trigger triggerArr[2];

int activeBalls = 0;

void initBalls (void) {
	int c;
	for (c=0; c<MAX_BALLS; c++){
		Ball* p = &ballArr[c];
		p->active=0;
	}
}

void destroyBall (Ball *b) {
	b->active = 0;
	activeBalls-=1;
}

void moveBall (Ball *b) {
	float y_wall,dx;
	int i;
	b->v_y-=b->time * GRAVITY;
	lcd_drawCircle(b->x,b->y,BALL_RADIUS,WHITE,1);

	// check for collision with wall
	y_wall = (b->v_y/b->v_x)*(WALL_X - b->x) + b->y;
	if (
			((WALL_X>b->x)?((WALL_X-b->v_x)<=b->x):((WALL_X-b->v_x)>=b->x)) &&
			(y_wall<(WALL_HEIGHT+BALL_RADIUS))
		) {
		destroyBall(b);
		return;
	}

	// check for collision with cannon
	for(i=0;i<2;++i) {
		dx = b->x - cannonArr[i].x;
		if (sqrt(dx*dx + b->y*b->y)<(BALL_RADIUS+CANNON_RADIUS)) {
			cannonArr[i].x = cannonArr[i].spawn_x;
		}
	}

	b->time+=1;
	b->x+=b->v_x;
	b->y+=b->v_y;

	if (REBOUND_X) {
		if (b->x < 0.0 || b->x > 128.0) {
			b->v_x *= -1;
		}
	}
	if (REBOUND_Y) {
		if (b->y > 64.0) {
			b->v_y *= -1;
		}
	}

	lcd_drawCircle(b->x,b->y,BALL_RADIUS,BLACK,1);
	if (b->y < -BALL_RADIUS) {
		destroyBall(b);
	}
}

Ball* getFreeBall(void) {
	int c;
	for (c=0; c<MAX_BALLS; c++){
		Ball* p = &ballArr[c];
		if (p->active == 0)
			return p;
	}
	return 0;
}

void moveActiveBalls(void) {
	Ball* ballPtr = ballArr;
	Ball* endPtr = ballArr + sizeof(ballArr)/sizeof(ballArr[0]);
	while ( ballPtr < endPtr ){
	   if (ballPtr->active)
		   moveBall(ballPtr);
	   ballPtr++;
	}
}

void drawCannon (Cannon *c, int color) {
	lcd_drawCircle(c->x, 0, CANNON_RADIUS, color, 0);
	lcd_drawLine(c->x,0,c->x+BARREL_LENGTH*cos(c->angle),BARREL_LENGTH*sin(c->angle),color);
}

void updateCannon(int index) {
	//char destLabel[10];
	Cannon* c = &cannonArr[index];
	// clear previous cannon
	drawCannon(c,WHITE);

	// debug
	//intToStr((int)c->destination_x, 5, '0', &destLabel);
	//lcd_drawString(46*index, 0,0,0, 0,0, &destLabel, 1, 0);

	// update barrel angle
	c->angle = M_PI*(adc_getValue(index+1)/255.0);

	// update x position
	// 1. if the cannon reached the destination, determine a new one
	if (fabs(c->destination_x - c->x)<1.0){
		c->destination_x = random()%(64-(2*CANNON_RADIUS)) + CANNON_RADIUS + index*64;
	}
	// 2. move towards that destination
	if (c->destination_x > c->x) {
		c->x+=CANNON_SPEED;
	} else {
		c->x-=CANNON_SPEED;
	}

	// draw new cannon
	drawCannon(c,BLACK);
}

void initCannons(void) {
	cannonArr[0].angle = M_PI;
	cannonArr[1].angle = M_PI;
	cannonArr[0].x = 7;
	cannonArr[1].x = 121;
	cannonArr[0].spawn_x = 7;
	cannonArr[1].spawn_x = 121;
	cannonArr[0].destination_x = 28;
	cannonArr[1].destination_x = 100;
}

void shootBall(int index) {
	Cannon *c = &cannonArr[index];
	Ball *b;
	float initialSpeed;
	if (activeBalls == MAX_BALLS) {
		return;
	}
	b = getFreeBall();
	b->active=1;
	activeBalls+=1;
	b->time=0;
	b->x = c->x + cos(c->angle)*(BARREL_LENGTH+BALL_RADIUS);
	b->y = sin(c->angle)*(BARREL_LENGTH+BALL_RADIUS);
	initialSpeed = BALL_INITIAL_SPEED + (float)(triggerArr[index].charge) / CHARGE_DIVIDER;
	b->v_x = cos(c->angle) * initialSpeed;
	b->v_y = sin(c->angle) * initialSpeed;
}

void initTriggers(void) {
	triggerArr[0].charge=0;
	triggerArr[1].charge=0;
	triggerArr[0].pressed=0;
	triggerArr[1].pressed=0;
}

void checkTrigger(int index) {
	Trigger *t = &triggerArr[index];
	int state = buttons_get(index);

	if (state) {
		t->charge++;
		t->pressed=1;
	} else {
		if (t->pressed) {
			shootBall(index);
			t->pressed=0;
			t->charge=0;
		}
	}
}

void paintWall (void) {
	lcd_drawLine(WALL_X,0,WALL_X,WALL_HEIGHT,BLACK);
}

void main(void) {
	// init hardware
	lcd_init();
	adc_init();
	buttons_init();
	random_init();

	// init game memory
	initBalls();
	initCannons();
	initTriggers();

	// main loop
	for (;;) {

		moveActiveBalls();

		updateCannon(0);
		updateCannon(1);

		checkTrigger(0);
		checkTrigger(1);

		paintWall();

		delay_ms(FRAME_DURATION);
		lcd_flush();
	}
}




/*void main(void) {
	uint16_t x,y;
	lcd_init();
	adc_init();
	x=0;y=0;
	for (;;) {
		lcd_drawLine(63,32,x,y,0);
		x=adc_getValue(1)/2;
		y=adc_getValue(2)/4;
		lcd_drawLine(63,32,x,y,1);
		lcd_flush();
	}
}
*/
