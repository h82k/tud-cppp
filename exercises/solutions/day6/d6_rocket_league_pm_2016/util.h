#ifndef __UTIL_H__
#define __UTIL_H__

#define NULL 0

#ifndef M_PI
#define M_PI 3.1415926f
#endif

typedef struct
{
	float x, y;
} Vector2F;

void delay(long de);
float vector_dot(Vector2F a, Vector2F b);

#endif // __UTIL_H__
