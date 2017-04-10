#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "util.h"

typedef struct 
{
	Vector2F Location;
	Vector2F Velocity;
	Vector2F Force;
	float Radius;
	float Mass;
	float Friction;
	int IsUsed;
} PhysicsObject;

#define PHYSICS_OBJECT_COUNT 3

#define PHYSICS_RESTITUTION 0.4f

void physics_init(float maxX, float maxY);
void physics_update(float dt);
void physics_add_force(PhysicsObject* o, Vector2F f);
PhysicsObject* physics_create(float x, float y, float radius, float mass);

#endif // __PHYSICS_H__
