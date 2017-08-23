#include "init.h"

int main(){
    initBoard();
    controlLedsInit();
    while(1) {
        controlLeds();
        delay(1000);
    }
}