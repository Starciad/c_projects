#include <stdio.h>
#include "game.h"
#include "player.h"

player main_player;

void game_initialize(void) {
    char player_name[50];

    printf("Enter your player name: ");
    fgets(player_name, sizeof(player_name), stdin);

    player_initialize(&main_player, player_name);
}

void game_start(void) {
    printf("Game started!\n");

    // Game loop
    while (player_is_alive(&main_player)) {
        break;
    }
}
