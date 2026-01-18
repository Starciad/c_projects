#include "enemy.h"
#include "random.h"

entity enemy_create(int challenge_level) {
    int health = random_int(1, 5) + challenge_level * 2;
    int mana = random_int(1, 3) + challenge_level;

    return (entity) {
        .coins = (challenge_level * 10) + random_int(5, 15),
        .base_attack = challenge_level,
        .critical_chance = challenge_level + random_int(5, 10),
        .current_health = health,
        .current_mana = mana,
        .defense = challenge_level + random_int(0, 2),
        .maximum_health = health,
        .maximum_mana = mana,
        .is_defending = false,
        .is_preparing_attack = false,
    };
}
