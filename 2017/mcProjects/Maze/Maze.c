/*
 * Maze game for the C/C++ lab Microcontroller of the real-time 
 * systems lab at TU Darmstadt.
 *
 * Author: Nicolas Himmelmann
 */
#include "Maze.h"       
#include "display.h"   
#include "analog.h"  
                                                 
//Maze dimensions, must be odd
int width = 67, height = 41;
int blocksize = 7;
int offsetX;
int offsetY;    

int bgColor = BLACK;
int fgColor = CYAN; 
int goalColor = YELLOW;
   
Node * player1; 
int player1Color = RED;    
Node * player2;            
int player2Color = MAGENTA;

Node * goalPos;
                          
bool goalReached1 = false;
bool goalReached2 = false;
         
//Nodes array
Node * nodes;

//Generate random value by reading
//the last bit of the analog channels
uint16_t getRandom() {
  uint16_t random = 0;
  for(int i=0; i<2; ++i) {
    random = random << 7;
    uint8_t a, b, c, d, e, f, g;
    getAnalogValues(&a, &b, &c, &d, &e, &f, &g);  
    random |= (a&1) << 0 | (b&1) << 1 | (c&1) << 2 | (d&1) << 3 | (e&1) << 4 | (f&1) << 5 | (g&1) << 6;
  }
  return random;
}

Node * getPlayer1() { return player1; }
Node * getPlayer2() { return player2; }       
int getPlayer1Color() { return player1Color; }
int getPlayer2Color() { return player2Color; }


int initMaze( )
{          
  //Seed random generator
  srand(getRandom());
  
  offsetX = (480 - width*blocksize)/2;
  offsetY = 0;  
  
	int x, y;
	Node *n;
	
	//Allocate memory for maze
	nodes = calloc( width * height, sizeof( Node ) );
	if ( nodes == NULL ) return 1;
		
	//Setup crucial nodes
	for ( x = 0; x < width; x++ )
	{
		for ( y = 0; y < height; y++ )
		{
			n = nodes + x + y * width;
			if ( x * y % 2 ) 
			{
				n->x = x;
				n->y = y;
				n->dirs = 15; //Assume that all directions can be explored (4 lowest bits set)
				n->wall = false; 
			}
			else n->wall = true; //Add walls between nodes
		}
	}          
  
  //Initialize player 1 position            
  player1 = calloc( 1, sizeof( Node ) );   
  player1->x = 1;
  player1->y = 1;
  
  //Initialize player 2 position            
  player2 = calloc( 1, sizeof( Node ) );   
  player2->x = width-2;
  player2->y = height-2;
  
  //Initialize goal position
  goalPos = calloc(1, sizeof(Node));
  goalPos->x = width/2;
  goalPos->y = height/2; 
  
	return 0;
}

Node * linkNode( Node *n ) {
	//Connects node to random neighbor (if possible) and returns
	//address of next node that should be visited
	int x, y;
	char dir;
	Node *dest;
	              
	//Nothing can be done if null pointer is given - return
	if ( n == NULL ) return NULL;
	
	//While there are directions still unexplored
	while ( n->dirs )
	{
		//Randomly pick one direction
		dir = ( 1 << ( rand( ) % 4 ) );
		
    //If it has already been explored - try again
		if ( ~n->dirs & dir ) continue;
		
		//Mark direction as explored
		n->dirs &= ~dir;
		
		//Depending on chosen direction
		switch ( dir )
		{
			//Check if it's possible to go right
			case 1:
				if ( n->x + 2 < width )
				{
					x = n->x + 2;
					y = n->y;
				}
				else continue;
				break;
			
			//Check if it's possible to go down
			case 2:
				if ( n->y + 2 < height )
				{
					x = n->x;
					y = n->y + 2;
				}
				else continue;
				break;
			
			//Check if it's possible to go left	
			case 4:
				if ( n->x - 2 >= 0 )
				{
					x = n->x - 2;
					y = n->y;
				}
				else continue;
				break;
			
			//Check if it's possible to go up
			case 8:
				if ( n->y - 2 >= 0 )
				{
					x = n->x;
					y = n->y - 2;
				}
				else continue;
				break;
		}
		
		//Get destination node into pointer (makes things a tiny bit faster)
		dest = nodes + x + y * width;
		
		//Make sure that destination node is not a wall
		if ( dest->wall == false)
		{
			//If destination is a linked node already - abort
			if ( dest->parent != NULL ) continue;
			
			//Otherwise, adopt node
			dest->parent = n;
			
			//Remove wall between nodes
			nodes[n->x + ( x - n->x ) / 2 + ( n->y + ( y - n->y ) / 2 ) * width].wall = false;
			
			//Return address of the child node
			return dest;
		}
	}
	
	//If nothing more can be done here - return parent's address
	return n->parent;   
}

void generateMaze() { 
	Node *start, *last;      
  
  //Setup start node
	start = nodes + 1 + width;
	start->parent = start;
	last = start;
  
  //Connect nodes until start node is reached and can't be left
	while ( ( last = linkNode( last ) ) != start );  
}

void drawMaze() {
  initCursor_s();
  
	uint16_t x, y;
  
  for ( x = 0; x < width; x++ )
	{
		for ( y = 0; y < height; y++ )
		{
			if(nodes[y * width + x].wall) {
        fillRect(offsetX + x*blocksize, offsetY + y*blocksize, blocksize, blocksize, fgColor);  
      }
    }
	}    
                          
  drawPlayerPos(player1, player1Color);
  drawPlayerPos(player2, player2Color);
  drawGoalPos();
}

void drawPlayerPos(Node * player, int color) {
  fillRect(offsetX + (player->x)*blocksize, offsetY + (player->y)*blocksize, blocksize, blocksize, color); 
}

void drawGoalPos() {
  //Draw goal node in background color
  fillRect(offsetX + (goalPos->x)*blocksize, offsetY + (goalPos->y)*blocksize, blocksize, blocksize, goalColor); 
  //Set goal node as accessible
  Node * goalNode = nodes + (goalPos->x)*height + goalPos->y;
  goalNode->wall = false;
}

bool checkGoalReached(Node * player, bool p1) {
  if((player->x == goalPos->x) && (player->y == goalPos->y)) {
    if(p1) goalReached1 = true;
    else goalReached2 = true;
    return true;
  }
  return false;
}

void clearRect(int x, int y) {
   fillRect(offsetX + x*blocksize, offsetY + y*blocksize, blocksize, blocksize, bgColor);
}

void movePlayer(Node * player, bool p1) {
  //Prevent movement of player once he reached the goal
  if(p1 && goalReached1) return;
  if(!p1 && goalReached2) return;
  
  //Read Joystick values
  uint8_t analog11;
  uint8_t analog12;
  uint8_t j1x;
  uint8_t j1y; 
  uint8_t j2x;
  uint8_t j2y;
  uint8_t analog17;
  getAnalogValues(&analog11, &analog12, &j2x, &j1x, &analog17, &j1y, &j2y);
                       
  int upper = 220;
  int lower = 180;
  
  bool moved = false; 
  //Save last position in case we move and have to 
  //clear the last position rectangle
  int lastX = player->x;
  int lastY = player->y;           
  
  if((p1 && (j1x >= upper)) || (!p1 && (j2x >= upper))) {
    //Left                                                
    Node * leftNode = nodes + (player->y*width) + player->x - 1; 
    int x = leftNode->x;
    int y = leftNode->y;               
    if(!leftNode->wall) {   
      player->x--;
      moved = true;
    }
  }
  else if((p1 && (j1x < lower)) || (!p1 && (j2x < lower))) {
    //Right                                      
    Node * rightNode = nodes + (player->y*width) + player->x + 1;
    int x = rightNode->x;
    int y = rightNode->y;
    bool wall = rightNode->wall;
    if(!rightNode->wall) {                
      player->x++; 
      moved = true;
    }
  } 
  else if((p1 && (j1y < lower)) || (!p1 && (j2y < lower)))  {
    //Up                                                              
    Node * topNode = nodes + (player->y+1)*width + player->x;
    int x = topNode->x;
    int y = topNode->y;    
    if(!topNode->wall) {                   
      player->y++;
      moved = true;
    }
  }
  else if((p1 && (j1y >= upper)) || (!p1 && (j2y >= upper))) {
    //Down                                                             
    Node * downNode = nodes + (player->y-1)*width + player->x; 
    int x = downNode->x;
    int y = downNode->y;    
    if(!downNode->wall) {                
      player->y--; 
      moved = true;
    }        
  }
  if(moved) {
    drawPlayerPos(player, (p1) ? player1Color : player2Color);
    clearRect(lastX, lastY); 
  }             
}