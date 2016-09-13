#include "player.h"

#include "input.h"
#include "segment.h"
#include "display.h"

#include <math.h>

Player players[MAX_PLAYERS];

void players_init(void)
{
	int i;
	
	memset(players, 0, sizeof(players));
	
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		Player* player = &players[i];
		
		player->PhysicsObject = physics_create(i == 0 ? 20 : LCD_WIDTH - 20, 32, PLAYER_RADIUS, PLAYER_MASS);
		//player->PhysicsObject->Friction = PLAYER_FRICTION;
	}
	
	players_reset();
}

void players_update(float dt)
{
	int i;
	Vector2F force;
	
	// Update score display
	segment_set_left(players[0].Score);
	segment_set_right(players[1].Score);
	
	// Update driving state and analog input
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		Player* player = &players[i];
		
		player->IsDriving = input_button_down(i);
		player->AnalogInput = input_get_analog(i);
	}
	
	// Update movement
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		Player* player = &players[i];
		
		// Update the rotation
		//player->Angle = player->Angle + 2.0f * player->AnalogInput * dt;
		player->Angle = (i == 0 ? 0 : M_PI) + 3.0f * player->AnalogInput * M_PI;
		
		/*
		// Clamp angle between -pi and +pi
		while(player->Angle > M_PI)
			player->Angle -= 2.0f * M_PI; 
		while(player->Angle < -M_PI)
			player->Angle += 2.0f * M_PI; 
		*/
		
		if(player->IsDriving)
		{
			// Apply the force
			force.x = cos(player->Angle) * PLAYER_MOVE_FORCE;
			force.y = sin(player->Angle) * PLAYER_MOVE_FORCE;
			physics_add_force(player->PhysicsObject, force);
		}
	}
}

void players_draw(void)
{
	int i;
	float fx, fy;
	
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		Player* player = &players[i];
		display_drawCircle(player->PhysicsObject->Location.x, player->PhysicsObject->Location.y, player->PhysicsObject->Radius);
		
		fx = 5.0f * cos(player->Angle);
		fy = 5.0f * sin(player->Angle);
		
		display_drawPixel(player->PhysicsObject->Location.x + (int)fx, player->PhysicsObject->Location.y + (int)fy, 1);
	}
}

Player* players_get(int index)
{
	if(index < 0 || index > MAX_PLAYERS)
	{
		return NULL;
	}
	
	return &players[index];
}

void players_reset(void)
{
	int i;
	
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		Player* player = &players[i];
		
		// Reset location and angle
		player->PhysicsObject->Velocity.x = 0;
		player->PhysicsObject->Velocity.y = 0;
		player->PhysicsObject->Location.x = i == 0 ? 20 : LCD_WIDTH - 20;
		player->PhysicsObject->Location.y = 32;
		player->Angle = i == 0 ? 0 : M_PI;
	}
}