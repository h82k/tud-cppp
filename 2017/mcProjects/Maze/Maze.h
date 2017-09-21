/*
 * Maze game for the C/C++ lab Microcontroller of the real-time 
 * systems lab at TU Darmstadt.
 *
 * Author: Nicolas Himmelmann
 */
#ifndef MAZE_H__
#define MAZE_H__

#include <stdbool.h>
#include <stdlib.h>   
                     
typedef struct
{
	int x, y;     //Node position
	void *parent; //Pointer to parent node
	bool wall;       //true = Wall, false = no wall
	char dirs;    //Directions that stil haven't been explored
} Node;       

Node * getPlayer1();   
Node * getPlayer2();   
int getPlayer1Color();
int getPlayer2Color();

int initMaze();
Node * linkNode( Node * n );
void generateMaze();
void drawMaze();             
void clearRect(int x, int y);
void drawPlayerPos(Node * player, int color);
void drawGoalPos();   
bool checkGoalReached(Node * player, bool p1);
void movePlayer(Node * player, bool p1);


#endif