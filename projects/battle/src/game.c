#include <stdio.h>
#include "enemy.h"
#include "entity.h"
#include "game.h"
#include "player.h"

static entity player;
static entity enemy;

static uint8_t battles_won = 0;

static bool is_possible_next_battle(void) {
    return entity_is_alive(&player);
}

static bool is_possible_continue_battle(void) {
    return entity_is_alive(&player) && entity_is_alive(&enemy);
}

static void display_welcome_message(void) {
    printf("Welcome to the Battle Game!\n");
    printf("Prepare to face off against fearsome enemies!\n");
}

static void display_battle_introduction(void) {

}

static void display_battle_stats(void) {

}

static void display_entities_stats(void) {
    printf("Player (%d/%d)\n", player.current_health, player.maximum_health);
    printf("Enemy (%d/%d)\n", enemy.current_health, enemy.maximum_health);
    printf("\n");
}

static void perform_attack(void) {

}

static void perform_defend(void) {

}

static void display_magic_menu(void) {

}

static void display_use_item_menu(void) {
}

static void perform_player_turn(void) {
    printf("It's your turn! What will you do?\n");
    printf("\n");
    printf("1. Attack (%d - %d damage) (%d%% critical chance)\n", 1, 1, 1);
    printf("2. Magic\n");
    printf("3. Defend\n");
    printf("4. Use Item\n");
    printf("\n");

    repeat_choice:
    printf("Choose an action: ");

    uint8_t choice;
    scanf("%hhu", &choice);

    switch (choice) {
        case 1:
            perform_attack();
            break;
        case 2:
            display_magic_menu();
            break;
        case 3:
            perform_defend();
            break;
        case 4:
            display_use_item_menu();
            break;
        default:
            printf("Invalid choice!\n");
            goto repeat_choice;
            break;
    }
}

static void perform_enemy_turn(void) {

}

// =========================================== //

void game_initialize(void) {
    player = player_create();

    battles_won = 0;
}

void game_start(void) {
    display_welcome_message();

    // Game loop
    do {
        // Create a new enemy for the battle
        // Challenge level is based on battles won
        enemy = enemy_create(battles_won + 1);

        // Battle Introduction
        display_battle_introduction();

        // Battle loop
        do {
            display_battle_stats();

            // Player's turn
            display_entities_stats();
            perform_player_turn();
            
            // Enemy's turn
            display_entities_stats();
            perform_enemy_turn();
        } while (is_possible_continue_battle());

        // Check if player is still alive
        if (entity_is_alive(&player)) {
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
