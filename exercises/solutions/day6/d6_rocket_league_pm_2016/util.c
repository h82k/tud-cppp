#include "util.h"

#include "mb96348hs.h"

void delay(long de)
{
	long d;
	
	for(d = 0; d < de; d++)
		__wait_nop();
}

float vector_dot(Vector2F a, Vector2F b)
{
	return a.x * a.x + b.y * b.y;
}