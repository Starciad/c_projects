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
#include "random.h"

static entity player;
static entity enemy;

static uint16_t battles_won = 0;
static uint16_t challenge_level = 1;

// =============================================== //
// System functions

static void game_sleep(uint16_t milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds); // Windows Sleep takes milliseconds
    #else
        sleep(milliseconds / 1000); // Unix sleep takes seconds
    #endif
}

// =============================================== //

static void battle_rewards(void) {
    const uint32_t coins_earned = enemy.coins;
    
    // Coins reward
    player.coins += coins_earned;

    printf("* You earned %u coins from the battle!\n", coins_earned);
}

static void player_level_up(void) {
    puts("");
    puts("Choose what you want to improve:");
    puts("");
    printf("1. Increase Base Attack (+1) [%d >> %d]\n", player.base_attack, player.base_attack + 1);
    printf("2. Increase Critical Chance (+1%%) [%d%% >> %d%%]\n", player.critical_chance, player.critical_chance + 1);
    printf("3. Increase Defense (+1) [%d >> %d]\n", player.defense, player.defense + 1);
    printf("4. Increase Maximum Health (+5) [%d >> %d]\n", player.maximum_health, player.maximum_health + 5);
    puts("");

    repeat_level_up_choice:
    printf("Enter your choice: ");

    uint8_t choice;
    scanf("%hhu", &choice);

    switch (choice) {
        case 1:
            player.base_attack += 1;
            printf("\n* Your Base Attack has increased to %d!\n", player.base_attack);
            break;
        case 2:
            player.critical_chance += 1;
            printf("\n* Your Critical Chance has increased to %d%%!\n", player.critical_chance);
            break;
        case 3:
            player.defense += 1;
            printf("\n* Your Defense has increased to %d!\n", player.defense);
            break;
        case 4:
            player.maximum_health += 5;
            player.current_health += 5; // Also heal the player
            printf("\n* Your Maximum Health has increased to %d!\n", player.maximum_health);
            break;
        default:
            puts("Invalid choice!");
            goto repeat_level_up_choice;
            break;
    }
}

static void player_recover(void) {
    player.current_health = player.maximum_health;
    puts("* You feel rejuvenated after the last battle...");
}

// =============================================== //
// Display functions and battle actions

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
    puts("\n<=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=>\n");
}

static void display_entities_stats(void) {
    printf("Player (%d/%d)\n", player.current_health, player.maximum_health);
    printf("Enemy (%d/%d)\n", enemy.current_health, enemy.maximum_health);
    puts("");
}

static void perform_attack(void) {
    uint16_t damage = entity_get_attack_value(&player, ENTITY_ATTACK_VALUE_RANDOM);

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

    const uint16_t action_choice = random_int(0, 1);

    switch (action_choice) {
        // A random dialogue about the enemy. Does nothing on his turn.
        case 0:
            switch (random_int(0, 2)) {
                case 0:
                    puts("* The enemy glares at you menacingly.");
                    break;
                case 1:
                    puts("* The enemy seems to be sizing you up.");
                    break;
                case 2:
                    puts("* The enemy lets out a chilling roar.");
                    break;
                default:
                    break;
            }
            break;
        // Attack the player
        case 1:
        {
            uint16_t damage = entity_get_attack_value(&enemy, ENTITY_ATTACK_VALUE_RANDOM);

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
        // Should not happen, but just in case
        default:
            break;
    }
}

// =========================================== //
// Game functions

void game_start(void) {
    player = player_create();
    display_welcome_message();

    bool is_battle_won = false;

    // Game loop
    do {
        if (battles_won > 0) {
            // Message
            puts("* Congratulations on your victory!");
            game_sleep(2000);

            printf("* You have won %u battle(s)!\n", battles_won);
            game_sleep(2000);

            // Rewards
            battle_rewards();
            game_sleep(2000);

            // Level Up
            player_level_up();
            game_sleep(2000);

            // Camping
        
            // Player Recovery
            player_recover();
            game_sleep(2000);

            // Messages
            puts("* But... a new enemy approaches!");
            game_sleep(2000);
        }

        // Create a new enemy for the battle
        // Challenge level is based on battles won
        enemy = enemy_create(challenge_level);

        // Battle Introduction
        display_battle_introduction();

        // Battle loop
        is_battle_won = false;

        do {
            // Display battle stats
            display_battle_stats();
            display_entities_stats();

            // Player's turn
            perform_player_turn();
            game_sleep(1000);

            // Check if enemy is still alive
            if (!entity_is_alive(&enemy)) {
                is_battle_won = true;
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
        game_sleep(1000);

        if (is_battle_won) {
            battles_won++;
            challenge_level++;
            continue;
        } else {
            break;
        }
    } while (true);

    // Defeat message and cleanup
    puts("* Oh no! You've been defeated!");

    // Show final stats

    // End of game

    // Cleanup resources

    // Exit game
}
