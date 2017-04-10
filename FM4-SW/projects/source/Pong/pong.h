/**
 * Author: Laurenz Kamp
 * Created: 10.09.2015
 */



#define PLAYER_L		1
#define PLAYER_R		2

#define MIN_X			1
#define MAX_X			480
#define MIN_Y			1
#define MAX_Y			320

#define PEDAL_WIDTH		5
#define PEDAL_HEIGHT	32
#define PEDAL_HEIGHT_S	16
#define PEDAL_SMALL_AFTER	15
#define PEDAL_SMALL_LENGTH	3

#define MAX_BALLS		1
#define NEW_BALL_BOUNCES	10

static const unsigned char rvalues[] = {21, 4, 24, 19, 29, 1, 28, 52,
										23, 21, 20, 19, 59, 57, 41, 22,
										46, 63, 59, 56, 41, 36, 59, 29,
										37, 45, 44, 57, 31, 25, 36, 30,};

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

static unsigned char rand64(void)
{
//	static int pos = 0;
//
//	pos++;
//
//	if(pos >= 32) {
//		pos = 0;
//	}
//
//	return rvalues[pos];
	unsigned char r = rand();

	return r / 4;
}

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

	state.small_next = rand64() / 2;

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
  
  float32_t analog16fixed = analog16*1.25;
  float32_t analog3fixed = analog3*1.25;
	state.pos_pedal_l = 320 - (uint16_t)analog16fixed + 60;
	state.pos_pedal_r = 320 - (uint16_t)analog3fixed + 60;
  //state.pos_pedal_l = 160;
  //state.pos_pedal_r = 160;


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

  
	if(bounce != 0) {
		state.bounces += bounce;


		// Add balls.
		if(state.bounces > state.last_ball_added + NEW_BALL_BOUNCES) {
			state.add_ball_in = 10 + (rand64() / 2);
			state.last_ball_added = state.bounces;
		}


		if(state.bounces >= state.small_next) {
			state.small_next += rand64() / 2;
			state.pedal_count_l = PEDAL_SMALL_LENGTH;
			state.pedal_count_r = PEDAL_SMALL_LENGTH;
		}
		if(state.pedal_count_l > 0) {
			state.pedal_count_l--;
			state.size_pedal_l = PEDAL_HEIGHT_S;
		} else {
			state.size_pedal_l = PEDAL_HEIGHT;
		}
		if(state.pedal_count_r > 0) {
			state.pedal_count_r--;
			state.size_pedal_r = PEDAL_HEIGHT_S;
		} else {
			state.size_pedal_r = PEDAL_HEIGHT;
		}
	}

	if(state.add_ball_in > 0) {
		if(state.add_ball_in == 1) {
			state.pos_ball[state.num_balls].x = 64;
			state.pos_ball[state.num_balls].y = rand64();
			state.dir_ball[state.num_balls].y = 1;
			if(rand64() > 32) {
				state.dir_ball[state.num_balls].x = 1;
			} else {
				state.dir_ball[state.num_balls].x = -1;
			}
			state.num_balls++;
		}

		state.add_ball_in--;
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
    drawCircle(state.pos_ball[ball].x, state.pos_ball[ball].y, state.sizeOfBall, BLACK);
    state.pos_ball[ball].x += state.dir_ball[ball].x;
		state.pos_ball[ball].y += state.dir_ball[ball].y;
	}

	// Draw game state.
	//fillScreen(BLACK);

	for(ball = 0; ball < state.num_balls; ball++) {
		drawCircle(state.pos_ball[ball].x, state.pos_ball[ball].y, state.sizeOfBall, BLUE);
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

    //draw the outline of the game
  for(x = MIN_X - 1; x < MAX_X + 1; x++) {
		drawPixel(x, 0, WHITE);
		drawPixel(x, 319, WHITE);
	}
	for(y = MIN_Y - 1; y < MAX_Y + 1; y++) {
		drawPixel(0, y, WHITE);
		drawPixel(479, y, WHITE);
	}

	//lcd_flush();

	//wait(state.delay);

	return 0;
}