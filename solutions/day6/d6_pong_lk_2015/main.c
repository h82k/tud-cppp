#include "mb96348hs.h"


#include "io.h"
#include "display.h"
#include "pong.h"


void main(void) {
	int i = 0;
	int winner;
	int score_r = 0, score_l = 0;

	initIO();
	initADC();
	initLCD();
	lcd_clear();
	lcd_flush();

	seg_show(0);

	while(1) {

		while(PDR07_P0 & 1) {
			;
		}

		wait(3000000);

		pong_init();

		while((winner = pong_loop()) == 0) {
			;
		}

		if(winner == PLAYER_L && score_l < 9) {
			score_l++;
		} else if(winner == PLAYER_R && score_r < 9) {
			score_r++;
		}

		seg_show(score_r * 10 + score_l);
	}

	return;
}
