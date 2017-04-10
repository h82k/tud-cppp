/**
 *  This code is based on: https://github.com/Echtzeitsysteme/tud-cpp-exercises/tree/master/solutions/day6/d6_pong_lk_2015 
 *  The code is converted by Puria Izady for the Cypress FM4  microcontroller
 */

#include "pong.h"



void pong_init(void)
{
	//random_init();

	state.delay = 25000;

	state.bounces = 0;
	state.last_ball_added = 0;

	state.add_ball_in = 0;

	state.running = 1;
	state.winner = 0;

	state.pos_pedal_l = 0;
	state.pos_pedal_r = 0;
	state.size_pedal_l = PEDAL_HEIGHT;
	state.size_pedal_r = PEDAL_HEIGHT;
	state.pedal_count_l = 0;
	state.pedal_count_r = 0;


	state.small_next = 0;

	state.num_balls = 1;
  state.sizeOfBall = 3;
	state.pos_ball[0].x = 240;
	state.pos_ball[0].y = 160;
	state.dir_ball[0].x = 1;
	state.dir_ball[0].y = 1;
  
  uint16_t  x, y;
  
  //draw the outline of the game
  for(x = MIN_X - 1; x < MAX_X + 1; x++) {
		drawPixel(x, 0, WHITE);
		drawPixel(x, 319, WHITE);
	}
	for(y = MIN_Y - 1; y < MAX_Y + 1; y++) {
		drawPixel(0, y, WHITE);
		drawPixel(479, y, WHITE);
	}
  
}

int pong_loop(void)
{
	int diff;
	int x, y;
	int ball;
	int bounce = 0;
  
  //delete old pedals
  for(x = MIN_X; x < MIN_X + PEDAL_WIDTH; x++) {
		for(y = state.pos_pedal_l - (state.size_pedal_l / 2); y < state.pos_pedal_l + (state.size_pedal_l / 2); y++) {
			drawPixel(x, y, BLACK);
		}
	}

	for(x = MAX_X - PEDAL_WIDTH-1; x <= MAX_X-1; x++) {
		for(y = state.pos_pedal_r - (state.size_pedal_r / 2); y < state.pos_pedal_r + (state.size_pedal_r / 2); y++) {
			drawPixel(x, y, BLACK);
		}
	}
  
  float32_t analog16fixed = 255-analog16;
  float32_t analog13fixed = 255-analog13;
  //float32_t analog16fixed = 127;
  //float32_t analog13fixed = 127;

  if(analog16fixed<56){
    state.pos_pedal_l = map(analog16fixed, 0, 55, 0, 160);
  }
  else if(analog16fixed>=56){
    state.pos_pedal_l = map(analog16fixed, 56, 255, 161, 320);
  }

  if(analog13fixed<56){
    state.pos_pedal_r = map(analog13fixed, 0, 55, 0, 160);
  }
  else if(analog13fixed>=56){
    state.pos_pedal_r = map(analog13fixed, 56, 255, 161, 320);
  }

  
	// Check if ball is at upper or lower boundary.
	for(ball = 0; ball < state.num_balls; ball++) {
		if(state.pos_ball[ball].y <= MIN_Y) {
			state.dir_ball[ball].y = 1;
		} else if(state.pos_ball[ball].y >= MAX_Y) {
			state.dir_ball[ball].y = -1;
		}
	}

	// Check if ball bounced at pedal.
	for(ball = 0; ball < state.num_balls; ball++) {
		if(state.pos_ball[ball].x == MIN_X + PEDAL_WIDTH) {
			diff = state.pos_pedal_l - state.pos_ball[ball].y;
			if(diff < (state.size_pedal_l / 2) && diff > (0 - (state.size_pedal_l / 2))) {
				state.dir_ball[ball].x = 1;
				bounce++;
			}
		} else if(state.pos_ball[ball].x == MAX_X - PEDAL_WIDTH) {
			diff = state.pos_pedal_r - state.pos_ball[ball].y;
			if(diff < (state.size_pedal_r / 2) && diff > (0 - (state.size_pedal_r / 2))) {
				state.dir_ball[ball].x = -1;
				bounce++;
			}
		}
	}

  

 

	// Check if one player lost:
	for(ball = 0; ball < state.num_balls; ball++) {
		if(state.pos_ball[ball].x >= MAX_X) {
			// right player won!
			state.running = 0;
			state.winner = PLAYER_R;
		} else if(state.pos_ball[ball].x <= MIN_X) {
			state.running = 0;
			state.winner = PLAYER_L;
		}
	}

	if(state.running == 0) {
		return state.winner;
	}

	// Move balls:
	for(ball = 0; ball < state.num_balls; ball++) {
    /*    1px BALL
    //delete old position on screen
    drawPixel(state.pos_ball[ball].x, state.pos_ball[ball].y, BLACK); // Draw balls.
		drawPixel(state.pos_ball[ball].x, state.pos_ball[ball].y + 1, BLACK);
		drawPixel(state.pos_ball[ball].x, state.pos_ball[ball].y - 1, BLACK);
		drawPixel(state.pos_ball[ball].x + 1, state.pos_ball[ball].y, BLACK);
		drawPixel(state.pos_ball[ball].x - 1, state.pos_ball[ball].y, BLACK);
		state.pos_ball[ball].x += state.dir_ball[ball].x;
		state.pos_ball[ball].y += state.dir_ball[ball].y;
    */
    fillCircle(state.pos_ball[ball].x, state.pos_ball[ball].y, state.sizeOfBall, BLACK);
    state.pos_ball[ball].x += state.dir_ball[ball].x;
		state.pos_ball[ball].y += state.dir_ball[ball].y;
	}

	// Draw game state.
	//fillScreen(BLACK);

	for(ball = 0; ball < state.num_balls; ball++) {
		fillCircle(state.pos_ball[ball].x, state.pos_ball[ball].y, state.sizeOfBall, BLUE);
	}

	for(x = MIN_X; x < MIN_X + PEDAL_WIDTH; x++) {
		for(y = state.pos_pedal_l - (state.size_pedal_l / 2); y < state.pos_pedal_l + (state.size_pedal_l / 2); y++) {
			drawPixel(x, y, WHITE);
		}
	}

	for(x = MAX_X - PEDAL_WIDTH-1; x <= MAX_X-1; x++) {
		for(y = state.pos_pedal_r - (state.size_pedal_r / 2); y < state.pos_pedal_r + (state.size_pedal_r / 2); y++) {
			drawPixel(x, y, WHITE);
		}
	}

  /*
    //draw the outline of the game
  for(x = MIN_X - 1; x < MAX_X + 1; x++) {
		drawPixel(x, 0, WHITE);
		drawPixel(x, 319, WHITE);
	}
	for(y = MIN_Y - 1; y < MAX_Y + 1; y++) {
		drawPixel(0, y, WHITE);
		drawPixel(479, y, WHITE);
	}
  */

	//lcd_flush();

	//wait(state.delay);

	return 0;
}