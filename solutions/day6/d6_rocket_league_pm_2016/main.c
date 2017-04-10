#include "display.h"
#include "player.h"
#include "physics.h"
#include "input.h"
#include "segment.h"

#define BALL_MASS 7
#define BALL_RADIUS 2

Player* playerA;
Player* playerB;
PhysicsObject* ball;

void game_new_round(void)
{
	ball->Velocity.x = 0;
	ball->Velocity.y = 0;
	ball->Location.x = LCD_WIDTH / 2;
	ball->Location.y = LCD_HEIGHT / 2;
	players_reset();
}

void game_draw(void)
{
	int i;
	
	// reset buffer at startup
	display_clear();
	
	// Draw players
	players_draw();
	
	// Draw ball
	display_drawCircle(ball->Location.x, ball->Location.y, ball->Radius);

	// Draw goals
	for(i = 20; i < LCD_HEIGHT - 20; i++)
	{
		display_drawPixel(5, i, 1);
		display_drawPixel(LCD_WIDTH - 6, i, 1);
	}
	
	display_flush();
}

void game_update(void)
{
	// Check whether the ball is in the goal
	if(ball->Location.y >= 20 && ball->Location.y < LCD_HEIGHT - 20)
	{
		if(ball->Location.x <= 5)
		{
			playerA->Score++;
			game_new_round();
		}
		else if(ball->Location.x >= LCD_WIDTH - 5)
		{
			playerB->Score++;
			game_new_round();
		}
	}
}

void game_init(void)
{
	
}

int main(void)
{
	physics_init(LCD_WIDTH, LCD_HEIGHT);
	input_init();
	display_init();
	segment_init();
	players_init();
	
	playerA = players_get(0);
	playerB = players_get(1);
	
	ball = physics_create(LCD_WIDTH / 2, LCD_HEIGHT / 2, BALL_RADIUS, BALL_MASS);
	
	for (;;)
	{
		input_update();
		players_update(0.01f);
		physics_update(0.01f);
		game_update();
		game_draw();
	}
	
	return 0;
}