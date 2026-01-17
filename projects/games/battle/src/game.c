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

static bool is_first_battle = true;
static uint8_t battles_won = 0;

static void game_sleep(uint16_t milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds); // Windows Sleep takes milliseconds
    #else
        sleep(milliseconds / 1000); // Unix sleep takes seconds
    #endif
}

static void player_recover(void) {
    player.current_health = player.maximum_health;
}

static void display_welcome_message(void) {
    puts("* Welcome to the Battle Game!");
    game_sleep(2000);

    puts("* Try to survive as many battles as possible!");
    game_sleep(2000);

    puts("* Prepare to face off against fearsome enemies!");
    game_sleep(4000);
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

void game_start(void) {
    player = player_create();
    display_welcome_message();

    // Game loop
    do {
        if (!is_first_battle) {
            battles_won++;
        }

        if (battles_won > 0) {
            is_first_battle = false;

            // Message
            puts("* Congratulations on your victory!");
            printf("* You have won %u battles!\n", battles_won);

            // Level Up

            // Camping
        
            // Player Recovery
            player_recover();
            puts("* You feel rejuvenated after the last battle...");
            game_sleep(2000);
            puts("* But... a new enemy approaches!");
            game_sleep(2000);
        }

        // Create a new enemy for the battle
        // Challenge level is based on battles won
        enemy = enemy_create(battles_won + 1);

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

            // Check if player is still alive
            if (!entity_is_alive(&player)) {
                break;
            }
        } while (true);

        // Final delays before next battle or defeat
        game_sleep(2000);
    } while (entity_is_alive(&player));

    // Defeat message and cleanup
    puts("* Oh no! You've been defeated!");

    // Show final stats

    // End of game

    // Cleanup resources

    // Exit game
}
