#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include "enemy.h"
#include "entity.h"
#include "game.h"
#include "inventory.h"
#include "item.h"
#include "player.h"
#include "random.h"

static entity player;
static entity enemy;

static inventory player_inventory;
// static inventory enemy_inventory;

static int battles_won = 0;
static int challenge_level = 1;

// =============================================== //
// System functions

static void game_sleep(int milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds); // Windows Sleep takes milliseconds
    #else
        sleep(milliseconds / 1000); // Unix sleep takes seconds
    #endif
}

// =============================================== //

static void battle_rewards(void) {
    const int coins_earned = enemy.coins;
    
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

    int choice;
    scanf("%d", &choice);

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
    player.is_defending = false;
    player.is_preparing_attack = false;

    puts("* You feel rejuvenated after the last battle...");
}

// =============================================== //
// Display functions and battle actions

static void display_welcome_message(void) {
    puts("* Welcome to the Battle Game!");
    game_sleep(1800);

    puts("* Try to survive as many battles as possible!");
    game_sleep(1800);

    puts("* Prepare to face off against fearsome enemies!");
    game_sleep(4000);
}

static void build_entity_stats_line(const entity *e, const char *name) {
    printf("> %s (%d/%d) ", name, e->current_health, e->maximum_health);

    if (e->is_defending) {
        printf("[Defending] ");
    }

    if (e->is_preparing_attack) {
        printf("[Preparing Attack] ");
    }

    puts("");
}

static void display_battle_stats(void) {
    puts("\n<=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=>\n");
    build_entity_stats_line(&player, "Player");
    build_entity_stats_line(&enemy, "Enemy");
    puts("\n<=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=>\n");
}

static void perform_attack(void) {
    int damage = entity_get_attack_value(&player, ENTITY_ATTACK_VALUE_RANDOM);

    if (player.is_preparing_attack) {
        player.is_preparing_attack = false;

        damage = entity_get_attack_value(&player, ENTITY_ATTACK_VALUE_POWERFUL);

        puts("* You unleash your prepared powerful attack!");
        game_sleep(1800);
    } else if (entity_is_critical_hit(&player)) {
        damage = entity_get_attack_value(&player, ENTITY_ATTACK_VALUE_CRITICAL_HIT);

        game_sleep(1800);
        puts("* You dealt critical damage to the enemy!");
    }

    printf("* Your attack will deal %d damage to the enemy.\n", damage);
    game_sleep(1800);

    if (enemy.is_defending) {
        puts("* However, the enemy was defending itself and the damage was halved!");
        game_sleep(1800);
    }

    int actual_damage = entity_take_damage(&enemy, damage);

    if (enemy.defense > 0) {
        printf("* The enemy's defense reduced your damage by %d points.\n", enemy.defense);
        game_sleep(1800);
    }

    printf("* You attacked the enemy for %d damage!\n", actual_damage);
    game_sleep(1800);
}

static void perform_defend(void) {
    player.is_defending = true;
    player.is_preparing_attack = true;

    game_sleep(1800);
    puts("* You brace yourself to defend against the next attack!");
    game_sleep(1800);
    puts("* Enemy damage will be halved and subtracted from your current defense.");
    game_sleep(1800);
    puts("* You also prepare to deliver a strong attack next turn!");
    game_sleep(1800);
}

static void display_magic_menu(void) {

}

static bool perform_inventory_menu(void) {
    printf("* You open your inventory (%d item(s)):\n", inventory_count_items(&player_inventory));
    inventory_print(&player_inventory);
    puts("(type -1 to exit inventory)");
    game_sleep(1800);

    repeat_inventory_choice:
    printf("Select an item to use: ");
    int choice;
    scanf("%d", &choice);

    if (choice == -1) {
        puts("* You close your inventory.\n");
        return false;
    } else if (choice < 1 || choice > INVENTORY_CAPACITY) {
        puts("Invalid choice!");
        goto repeat_inventory_choice;
    } else if (player_inventory.items[choice - 1] == ITEM_NONE) {
        puts("There is no item in that slot!");
        goto repeat_inventory_choice;
    } else {
        item selected_item = player_inventory.items[choice - 1];
        item_use(&player, selected_item);
        inventory_remove_item(&player_inventory, selected_item);
        return true;
    }
}

static void perform_player_turn(void) {
    puts("It's your turn! What will you do?");
    puts("");
    printf("1. Attack (%d - %d damage) (%d%% critical chance)\n", entity_get_attack_value(&player, ENTITY_ATTACK_VALUE_MINIMUM), entity_get_attack_value(&player, ENTITY_ATTACK_VALUE_MAXIMUM), player.critical_chance);
    puts("2. Magic");
    puts("3. Defend");
    puts("4. Inventory");
    puts("");

    repeat_choice:
    printf("Choose an action: ");

    int choice;
    scanf("%d", &choice);

    puts("");

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
            if (!perform_inventory_menu()) {
                goto repeat_choice;
            }
            break;
        default:
            printf("Invalid choice!\n");
            goto repeat_choice;
            break;
    }
}

static void enemy_attack_action(void) {
    int damage = entity_get_attack_value(&enemy, ENTITY_ATTACK_VALUE_RANDOM);

    if (enemy.is_preparing_attack) {
        enemy.is_preparing_attack = false;

        damage = entity_get_attack_value(&enemy, ENTITY_ATTACK_VALUE_POWERFUL);

        puts("* The enemy unleashes its powerful attack!");
        game_sleep(1800);

    } else if (entity_is_critical_hit(&enemy)) {
        damage = entity_get_attack_value(&enemy, ENTITY_ATTACK_VALUE_CRITICAL_HIT);

        puts("* The enemy dealt critical damage to you!");
        game_sleep(1800);
    }

    printf("* The enemy's attack will deal %d damage to you.\n", damage);
    game_sleep(1800);

    if (player.is_defending) {
        puts("* However, you were defending yourself and the damage was halved!");
        game_sleep(1800);
    }

    int actual_damage = entity_take_damage(&player, damage);

    if (player.defense > 0) {
        printf("* Your defense reduced the damage by %d points.\n", player.defense);
        game_sleep(1800);
    }

    printf("* The enemy attacked you for %d damage!\n", actual_damage);
    game_sleep(1800);
}

static void perform_enemy_turn(void) {
    puts("* It's the enemy's turn!");
    game_sleep(1800);

    // If the enemy is preparing an attack, it must attack now
    if (enemy.is_preparing_attack) {
        enemy_attack_action();
        return;
    }

    const int action_choice = random_int(0, 2);

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
            game_sleep(1800);
            break;
        // Attack the player
        case 1:
        {
            enemy_attack_action();
            break;
        }
        // Defend itself
        case 2:
            enemy.is_defending = true;
            enemy.is_preparing_attack = true;

            puts("* The enemy braces itself to defend against the next attack!");
            game_sleep(1800);

            puts("* Furthermore, the enemy's next attack will come more powerful!");
            game_sleep(1800);
            break;
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
            game_sleep(1800);

            printf("* You have won %u battle(s)!\n", battles_won);
            game_sleep(1800);

            // Rewards
            battle_rewards();
            game_sleep(1800);

            // Level Up
            player_level_up();
            game_sleep(1800);

            // Camping
        
            // Player Recovery
            player_recover();
            game_sleep(1800);

            // Messages
            puts("* But... a new enemy approaches!");
            game_sleep(1800);
        }

        // Create a new enemy for the battle
        // Challenge level is based on battles won
        enemy = enemy_create(challenge_level);

        // Battle loop
        is_battle_won = false;

        do {
            // Display battle stats
            display_battle_stats();

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
        game_sleep(1800);

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
