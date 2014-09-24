#include "mb96348hs.h"

#define GAME_WIDTH 128
#define GAME_HEIGHT 64
#define GAME_MS_PER_FRAME 30.0
#define BALL_SPEED 50.0
#define BALL_RADIUS 3
#define ADC_COUNT 256
#define BAR_WIDTH 5
#define BAR_HEIGHT 16
#define CONVERT (GAME_HEIGHT - BAR_HEIGHT) / (ADC_COUNT-1)
#define LEFT_COLLISION GAME_WIDTH - 1 - BAR_WIDTH
#define RIGHT_COLLISION 0 + BAR_WIDTH

#include "library/util.h"
#include "library/lcd.h"
#include "library/adc.h"
#include "library/seg.h"
#include "library/buttons.h"
#include "math.h"

typedef struct ballData{
	float xPos;
	float yPos;
	float speed;
	float xDir;
	float yDir;
}ballData;

typedef struct playerData{
	float posLeft;
	float posRight;
	int pointsLeft;
	int pointsRight;
}playerData;

void ball_init(ballData* ball){
	// TODO make ranom better!!!
	float randomOne = random() % 1000 - 500 + 1;
	float randomTwo = (random() % 4 - 2) * randomOne;
	float factor = sqrt(randomOne*randomOne + randomTwo*randomTwo);
	randomOne /= factor;
	randomTwo /= factor;
	seg_num(randomOne);
	// BALL_SPEED = px/cycle
	// GAME_MS_PER_FRAME = ms/cycle
	// BALL_SPEED/GAME_MS_PER_FRAME = px/ms
	ball->xPos = GAME_WIDTH/2;
	ball->yPos = GAME_HEIGHT/2;
	ball->speed = BALL_SPEED / GAME_MS_PER_FRAME;
	ball->xDir = randomTwo;		//-4;
	ball->yDir = randomOne; 	//3
}

void restart(ballData* ball){
	// TODO make ranom better!!!
	float randomOne = random() % 1000 - 500 +                                                                     1;
	float randomTwo = (random() % 4 - 2) * randomOne;
	float factor = sqrt(randomOne*randomOne + randomTwo*randomTwo);
	randomOne /= factor;
	randomTwo /= factor;
	ball->xPos = GAME_WIDTH/2;
	ball->yPos = GAME_HEIGHT/2;
	ball->speed = BALL_SPEED / GAME_MS_PER_FRAME;
	ball->xDir = randomTwo;		//-4;
	ball->yDir = randomOne; 	//3
}

void player_init(playerData* player){
	player->posLeft = 0;
	player->posRight = 0;
	player->pointsLeft = 0;
	player->pointsRight = 0;
}

void ball_reflect(ballData* ball, int moveX){
	if(moveX)
		ball->xDir = - ball->xDir;
	else
		ball->yDir = - ball->yDir;
}

/*
void check_collision(ballData* ball){
	if(ball->yPos == 0 || ball->yPos == GAME_HEIGHT - 1){
		ball_reflect(ball, 0);
	}
	if(ball->xPos == 0 || ball->xPos == GAME_WIDTH - 1){
		ball_reflect(ball, 1);
	}
}
*/

int in_range(int ballPos, int barPos){
	if(ballPos <= barPos + BAR_HEIGHT + 1 && ballPos >= barPos - 1)
		return 1;
	else
		return 0;
}

void check_collision(ballData* ball, playerData* player){
	// check if a players bar collides with the ball
	/*
	if (in_range(ball->yPos, player->posRight))
		seg_num(1);
	else
		seg_num(0);
	*/
	if((int) ball->xPos >= LEFT_COLLISION && in_range(ball->yPos, player->posLeft)){
		ball_reflect(ball, 1);
		ball->speed *= 1.1;
		return;
	}
	if((int) ball->xPos <= RIGHT_COLLISION && in_range(ball->yPos, player->posRight)){
		ball_reflect(ball, 1);
		ball->speed *= 1.1;
		return;
	}
	// if not check if one player lost the game by let the ball touch the left or right wall
	if(ball->xPos == 0){
		player->pointsLeft++;
		restart(ball);
		return;
	}
	if(ball->xPos == GAME_WIDTH - 1){
		player->pointsRight++;
		restart(ball);
		return;
	}
	// check if the ball collides with the top or bottom wall
	if(ball->yPos == 0 || ball->yPos == GAME_HEIGHT - 1){
		ball_reflect(ball, 0);
		return;
	}
}

void ball_move(ballData* ball){
	// calculate new x position
	ball->xPos += ball->speed * ball->xDir;
	if(ball->xPos > GAME_WIDTH - 1)
		ball->xPos = GAME_WIDTH - 1;
	if(ball->xPos < 0)
		ball->xPos = 0;
	// calculate new y position
	ball->yPos += ball->speed * ball->yDir;
	if(ball->yPos > GAME_HEIGHT - 1)
		ball->yPos = GAME_HEIGHT - 1;
	if(ball->yPos < 0)
		ball->yPos = 0;
}

int convert(int pos){
	//seg_num((ADC_COUNT - 1 - pos) * CONVERT);
	return (ADC_COUNT - 1 - pos) * CONVERT;
}

void bar_move(playerData* player, int leftPos, int rightPos){
	player->posLeft = leftPos;
	player->posRight = rightPos;
}

void draw_bar(int xPos, int yPos, int width, int height, int black){
	if(width < 3){
		lcd_drawRect(xPos, yPos, width, height, black, 1);
	}
	else{
		lcd_drawLine(xPos, yPos + 1, xPos, yPos + height - 2, black);
		lcd_drawRect(xPos + 1, yPos, width - 2, height, black, 1);
		lcd_drawLine(xPos + width - 1, yPos + 1, xPos + width - 1, yPos + height - 2, black);
	}
}

void draw(ballData* ball, playerData* player){
	lcd_clear(0);
	// draw ball;
	lcd_drawCircle(ball->xPos, ball->yPos, BALL_RADIUS, 1, 1);
	// draw new right bar
	draw_bar(0, player->posRight, BAR_WIDTH, BAR_HEIGHT, 1);
	// draw new right bar
	draw_bar(GAME_WIDTH - BAR_WIDTH, player->posLeft, BAR_WIDTH, BAR_HEIGHT, 1);
}

void main(void) {
	// init stuff
	int playerSeg = 1;
	ballData ball;
	playerData player;
	lcd_init();
	adc_init();
	seg_init();
	buttons_init();
	random_init();
	ball_init(&ball);
	player_init(&player);
	for (;;) {
		// show points of one player
		/*
		if(!playerSeg)
			seg_num(player.pointsLeft);
		else
			seg_num(player.pointsRight);
			*/
		// toggle points view
		/*if(buttons_get(0))
			playerSeg = 0;
		if(buttons_get(1))
			playerSeg = 1;*/
		// move the bars with the A/D Converters
		bar_move(&player, convert(adc_getValue(2)), convert(adc_getValue(1)));
		// draw the ball and the bars
		draw(&ball, &player);
		// check collisions
		check_collision(&ball, &player);
		// move the ball
		ball_move(&ball);
		// wait for the next frame
		delay_ms(GAME_MS_PER_FRAME);
	}

}
