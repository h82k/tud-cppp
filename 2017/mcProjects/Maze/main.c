/*
 * Maze game for the C/C++ lab Microcontroller of the real-time 
 * systems lab at TU Darmstadt.
 *
 * Author: Nicolas Himmelmann
 */
#include "s6e2ccxj.h"
#include "init.h"    
#include "src/touch.h"  
#include "Maze.h"  
#include "src/display.h"
#include "lib/delay.h"  
#include "lib/gfx.h"
#include "pdl_header.h"

struct image {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[];
};
                   
#include "esLogo.h"
#include "cypressLogo.h"  
                                          
//stc_rtc_config_t stcRtcConfig; 
//stc_rtc_time_t stcTimeDate;
   
// Time variables
volatile uint8_t 
  //Global time
  minutes = 0,
  seconds = 0,
  //Player 1 finish time
  mins1 = 0,
  secs1 = 0,
  //Player 2 finish time
  mins2 = 0,
  secs2 = 0;

//Writes the time to the current display position
void writeTime(uint8_t mins, uint8_t secs) {  
  if(mins<10) {
    writeNumberOnDisplay_s(0);
  }
  writeNumberOnDisplay_s(&mins);
  writeAuto_s(':');
  if(secs<10) {
    writeNumberOnDisplay_s(0);
  }
  writeNumberOnDisplay_s(&secs); 
}

//Updates the time
void updateTime() {                   
  //Rtc_ReadDateTime(&RTC0, &stcTimeDate);
  ++seconds;
  if(seconds == 60) {
    seconds = 0;
    ++minutes;
  }
                            
  uint8_t secs = seconds;
  uint8_t mins = minutes;
  setCursor_s(210,306);      
  setTextSize_s(2);    
  setTextColor_s(WHITE);    
  writeTime(mins, secs);  
}

//Draws an image to the given _x and _y position
void drawImage(const struct image * img, int _x, int _y, int scale) {
  int x,y;                                          
  for(y = 0; y<img->height; ++y) {     
    int yPos = _y + img->height - y;
    for(x = 0; x < img->width*2; x+=2) {
      int tmp = y*img->width*2+x;
      uint16_t pxColor = ((uint16_t)img->pixel_data[tmp+1] << 8) | (uint16_t)img->pixel_data[tmp];
      int xPos = _x + x/2; 
      if(scale == 1) {
        drawPixel(xPos, yPos, pxColor);
      } else {
        fillRect(xPos*scale, yPos*scale, scale, scale, pxColor);
      }
    }
  }   
}

void writeGratulations() {
  fillScreen(BLACK);           
  initCursor_s();         
  setBackgroundColor_s(BLACK);
  
  setTextColor_s(MAGENTA);        
  setTextSize_s(4);        
  setCursor_s(0,270);     
  writeTextln_s("  Congratulations!");
  
  setTextSize_s(3);     
  setTextColor_s(YELLOW);
  writeTextln_s(" ");
  
  uint16_t mins=0, secs=0;
  
  writeText_s("      Player 1: ");              
  mins = mins1;
  secs = secs1;
  writeTime(mins, secs);
  writeTextln_s(" ");
 
  writeText_s("      Player 2: ");              
  mins = mins2;
  secs = secs2;
  writeTime(mins, secs);
                               
  drawImage(&esLogo, 20, 35, 1);
  drawImage(&cypressLogo, 145, 35, 1);
}

void initTopLine() {
  setCursor_s(210,306);
  writeTime(0, 0);     
  setCursor_s(10,306);
  setTextColor_s(getPlayer1Color());
  writeText_s("P1");   
  setCursor_s(450,306);
  setTextColor_s(getPlayer2Color());
  writeText_s("P2");
}                 

void writeDone(uint16_t x, uint16_t y, int color) {
  setCursor_s(x,y);         
  setTextSize_s(2);
  setTextColor_s(color);
  writeText_s("Done.");
}
       
bool p1Done = false;
bool p2Done = false;

int main() {
  initBoard();   
         
  initTopLine();
  initMaze();
  generateMaze();             
  drawMaze(); 
  
  int count = 0;
  Node * player1 = getPlayer1();
  Node * player2 = getPlayer2();
  while(1) {    
    movePlayer(player1, true);
    movePlayer(player2, false);
    if(checkGoalReached(player1, true) && !p1Done) {
       mins1 = minutes;
       secs1 = seconds;
       p1Done = true;
       writeDone(40,306, getPlayer1Color());
    }
    if(checkGoalReached(player2, false) && !p2Done) {
       mins2 = minutes;
       secs2 = seconds;
       p2Done = true; 
       writeDone(380,306, getPlayer2Color());
    }
    if(p1Done && p2Done) {
      writeGratulations();
      while(1);  
    }
    
    microDelay(50000);
    
    //Count how often we looped. 
    //Update time at 20 * 50ms = 1s
    if(count == 19) {
      updateTime();
      count = 0;  
    } else {
      ++count;  
    }
  }
  return 0;
}