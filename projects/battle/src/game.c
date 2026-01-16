#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "enemy.h"
#include "game.h"
#include "player.h"

player main_player;
enemy current_enemy;

static uint16_t battles_won = 0;

static bool is_possible_next_battle(void) {
    return player_is_alive(&main_player);
}

static bool is_possible_continue_battle(void) {
    return player_is_alive(&main_player) && enemy_is_alive(&current_enemy);
}

static void display_welcome_message(void) {
    printf("Welcome to the Battle Game!\n");
    printf("Prepare to face off against fearsome enemies!\n");
}

static void display_battle_introduction(void) {

}

static void display_battle_stats(void) {

}

static void perform_player_turn(void) {

}

static void perform_enemy_turn(void) {

}

// =========================================== //

void game_initialize(void) {
    char player_name[50];

    printf("Enter your player name: ");
    fgets(player_name, sizeof(player_name), stdin);

    player_initialize(&main_player, player_name);
}

void game_start(void) {
    display_welcome_message();

    // Game loop
    do {
        // Create a new enemy for the battle
        // Challenge level is based on battles won
        current_enemy = enemy_create(battles_won + 1);

        // Battle Introduction
        display_battle_introduction();

        // Battle loop
        do {
            // Player's turn
            display_battle_stats();
            perform_player_turn();
            
            // Enemy's turn
            display_battle_stats();
            perform_enemy_turn();
        } while (is_possible_continue_battle());

        // Check if player is still alive
        if (player_is_alive(&main_player)) {
            battles_won++;
            printf("You have won %u battles!\n", battles_won);
        } else {
            printf("Oh no! You've been defeated!\n");
            break; // Exit game loop if player is defeated
        }
    } while (is_possible_next_battle());

    // Defeat message and cleanup

    // Show final stats

    // End of game

    // Cleanup resources

    // Exit game
}
