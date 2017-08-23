#include "init.h"

int main(){
    initBoard();
    while(1) {
        printValues();
        delay(1000);
    }
}