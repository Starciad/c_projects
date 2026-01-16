#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int main(void) {
    srand(time(NULL));

    printf("Welcome to the Battle Game!\n");
    printf("Try to survive as many battles as possible!\n");

    game_initialize();
    game_start();
    
    return 0;
}