#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "physics.h"

#define MAX_PLAYERS 2

#define PLAYER_MASS 10
#define PLAYER_RADIUS 3
#define PLAYER_FRICTION 0.96f;
#define PLAYER_MOVE_FORCE 150.0f;

typedef struct
{
	PhysicsObject* PhysicsObject;
	float Angle;
	float AnalogInput;
	int IsDriving;
	int Score;
} Player;

void players_init(void);
void players_update(float dt);
void players_draw(void);
void players_reset(void);
Player* players_get(int index);

#endif