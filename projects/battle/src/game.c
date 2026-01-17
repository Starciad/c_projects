#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include "enemy.h"
#include "entity.h"
#include "game.h"
#include "player.h"

static entity player;
static entity enemy;

static uint8_t battles_won = 0;

static void game_sleep(uint16_t milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds); // Windows Sleep takes milliseconds
    #else
        usleep(milliseconds * 1000); // POSIX usleep takes microseconds
    #endif
}

static bool is_possible_next_battle(void) {
    return entity_is_alive(&player);
}

static bool is_possible_continue_battle(void) {
    return entity_is_alive(&player) && entity_is_alive(&enemy);
}

static void player_recover(void) {
    player.current_health = player.maximum_health;
}

static void display_welcome_message(void) {
    puts("Welcome to the Battle Game!");
    puts("Prepare to face off against fearsome enemies!");
}

static void display_battle_introduction(void) {

}

static void display_battle_stats(void) {
    puts("");
    puts("<=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=>");
    puts("");
}

static void display_entities_stats(void) {
    printf("Player (%d/%d)\n", player.current_health, player.maximum_health);
    printf("Enemy (%d/%d)\n", enemy.current_health, enemy.maximum_health);
    puts("");
}

static void perform_attack(void) {
    uint8_t damage = entity_get_attack_value(&player, ENTITY_ATTACK_VALUE_RANDOM);

    puts("");

    if (entity_is_critical_hit(&player)) {
        damage = entity_get_attack_value(&player, ENTITY_ATTACK_VALUE_CRITICAL_HIT);

        game_sleep(1000);
        puts("* You dealt critical damage to the enemy!");
    }

    entity_take_damage(&enemy, damage);

    game_sleep(1000);
    printf("* You attacked the enemy for %d damage!\n", damage);
}

static void perform_defend(void) {

}

static void display_magic_menu(void) {

}

static void display_use_item_menu(void) {

}

static void perform_player_turn(void) {
    puts("It's your turn! What will you do?");
    puts("");
    printf("1. Attack (%d - %d damage) (%d%% critical chance)\n", entity_get_attack_value(&player, ENTITY_ATTACK_VALUE_MINIMUM), entity_get_attack_value(&player, ENTITY_ATTACK_VALUE_MAXIMUM), player.critical_chance);
    puts("2. Magic");
    puts("3. Defend");
    puts("4. Use Item");
    puts("");

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
    puts("* It's the enemy's turn!");
    game_sleep(1000);

    // const uint8_t action_choice = random_int(1, 2); // Future: Randomize enemy actions
    const uint8_t action_choice = 1; // For now, enemy will always attack

    switch (action_choice) {
        case 1:
        {
            uint8_t damage = entity_get_attack_value(&enemy, ENTITY_ATTACK_VALUE_RANDOM);

            if (entity_is_critical_hit(&enemy)) {
                damage = entity_get_attack_value(&enemy, ENTITY_ATTACK_VALUE_CRITICAL_HIT);

                game_sleep(1000);
                puts("* The enemy dealt critical damage to you!");
            }

            entity_take_damage(&player, damage);

            game_sleep(1000);
            printf("* The enemy attacked you for %d damage!\n", damage);
            break;
        }
        default:
            break;
    }
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

        // Player's Level Up between battles
        // Future: Implement player leveling system
        
        // Player recovery between battles
        if (battles_won > 0) {
            player_recover();
            puts("* You feel rejuvenated after the last battle...");
            game_sleep(2000);
            puts("* But... a new enemy approaches!");
            game_sleep(2000);
        }

        // Battle Introduction
        display_battle_introduction();

        // Battle loop
        do {
            // Display battle stats
            display_battle_stats();
            display_entities_stats();

            // Player's turn
            perform_player_turn();
            game_sleep(1000);

            // Check if enemy is still alive
            if (!entity_is_alive(&enemy)) {
                break;
            }
            
            // Enemy's turn
            perform_enemy_turn();
            game_sleep(1000);
        } while (is_possible_continue_battle());

        // Check if player is still alive
        if (entity_is_alive(&player)) {
            battles_won++;
            printf("* You have won %u battles!\n", battles_won);
        } else {
            puts("* Oh no! You've been defeated!");
            break; // Exit game loop if player is defeated
        }

        game_sleep(2000);
    } while (is_possible_next_battle());

    // Defeat message and cleanup

    // Show final stats

    // End of game

    // Cleanup resources

    // Exit game
}
