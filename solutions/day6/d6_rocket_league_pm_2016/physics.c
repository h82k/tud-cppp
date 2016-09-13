#include "physics.h"

#include <math.h>

float physicsMaxX, physicsMaxY;
PhysicsObject physicsObjects[PHYSICS_OBJECT_COUNT];

void physics_init(float maxX, float maxY)
{
	// Set the bounds
	physicsMaxX = maxX;
	physicsMaxY = maxY;
	
	// Zero all physics objects (=making them inactive)
	memset(physicsObjects, 0, sizeof(physicsObjects));
}

int are_colliding(PhysicsObject* a, PhysicsObject* b, Vector2F* displacement)
{
	float dx = (a->Location.x - b->Location.x);
	float dy = (a->Location.y - b->Location.y);
	float size = a->Radius + b->Radius;
	float dstSq = dx * dx + dy * dy;
	
	int colliding = dstSq < size * size;
	
	if(colliding)
	{
		displacement->x = dx;
		displacement->y = dy;
	}
	
	return colliding;
}

void check_bounds(PhysicsObject* o)
{
	// Min X
	if(o->Location.x < o->Radius)
	{
		o->Location.x = o->Radius;
		if(o->Velocity.x < 0)
			o->Velocity.x = -o->Velocity.x;
	}
	
	// Max X
	if(o->Location.x > physicsMaxX - o->Radius)
	{
		o->Location.x = physicsMaxX - o->Radius;
		if(o->Velocity.x > 0)
			o->Velocity.x = -o->Velocity.x;
	}
	
	// Min Y
	if(o->Location.y < o->Radius)
	{
		o->Location.y = o->Radius;
		if(o->Velocity.y < 0)
			o->Velocity.y = -o->Velocity.y;
	}
	
	// Max Y
	if(o->Location.y > physicsMaxY - o->Radius)
	{
		o->Location.y = physicsMaxY - o->Radius;
		if(o->Velocity.y > 0)
			o->Velocity.y = -o->Velocity.y;
	}
}

void physics_update(float dt)
{	
	int i, j;
	float dst, momentumToward, resolutionDistance;
	
	for(i = 0; i < PHYSICS_OBJECT_COUNT; i++)
	{
		PhysicsObject* o = &physicsObjects[i];
		
		// Update velocity
		o->Velocity.x += o->Force.x * dt;
		o->Velocity.y += o->Force.y * dt;
		
		// Apply friction
		o->Velocity.x = o->Velocity.x * o->Friction;
		o->Velocity.y = o->Velocity.y * o->Friction;
		
		// Update location
		o->Location.x += o->Velocity.x * dt;
		o->Location.y += o->Velocity.y * dt;
		
		// Clear forces
		o->Force.x = 0;
		o->Force.y = 0;
	}
	
	// Collision checks and resolution
	for(i = 0; i < PHYSICS_OBJECT_COUNT; i++)
	{
		PhysicsObject* a = &physicsObjects[i];
		
		if(a->IsUsed)
		{
			for(j = i + 1; j < PHYSICS_OBJECT_COUNT; j++)
			{
				// Check whether objects are colliding
				PhysicsObject* b = &physicsObjects[j];
					
				Vector2F displacement;
				if(b->IsUsed && are_colliding(a, b, &displacement))
				{
					// Normalize (=hit normal)
					dst = sqrt(displacement.x*displacement.x + displacement.y*displacement.y);
					displacement.x /= dst;
					displacement.y /= dst;
					
					// Find the distance required to seperate the circles
					resolutionDistance = a->Radius + b->Radius - dst + 2;
					
					a->Location.x += resolutionDistance * displacement.x / 2;
					a->Location.y += resolutionDistance * displacement.y / 2;
					b->Location.x -= resolutionDistance * displacement.x / 2;
					b->Location.y -= resolutionDistance * displacement.y / 2;
					
					// Ellastic collision
					momentumToward = a->Mass * vector_dot(a->Velocity, displacement) - b->Mass * vector_dot(b->Velocity, displacement);
					if(momentumToward > 0) 
					{
						Vector2F impulse;
						impulse.x = PHYSICS_RESTITUTION * momentumToward * displacement.x * 0.5;
						impulse.y = PHYSICS_RESTITUTION * momentumToward * displacement.y * 0.5;
						
						a->Velocity.x += impulse.x / a->Mass;
						a->Velocity.y += impulse.y / a->Mass;
						
						b->Velocity.x -= impulse.x / b->Mass;
						b->Velocity.y -= impulse.y / b->Mass;
					}
				}
			}
		}
	}
	
	// Check the bounds for all objects
	for(i = 0; i < PHYSICS_OBJECT_COUNT; i++)
	{
		PhysicsObject* a = &physicsObjects[i];
		
		if(a->IsUsed)
		{
			check_bounds(a);
		}
	}
}

void physics_add_force(PhysicsObject* o, Vector2F f)
{
	o->Force.x += f.x;
	o->Force.y += f.y;
}

PhysicsObject* physics_create(float x, float y, float radius, float mass)
{
	int i ;
	
	for(i = 0; i < PHYSICS_OBJECT_COUNT; i++)
	{
		if(!physicsObjects[i].IsUsed)
		{
			PhysicsObject* o = &physicsObjects[i];
			
			o->Location.x = x;
			o->Location.y = y;
			o->Velocity.x = 0;
			o->Velocity.y = 0;
			o->Radius = radius;
			o->Mass = mass;
			o->IsUsed = 1;
			o->Friction = 0.96f;
			
			return o;
		}
	}
	
	return NULL;
}
