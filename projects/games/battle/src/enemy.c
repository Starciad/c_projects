#include "enemy.h"
#include "random.h"

entity enemy_create(uint16_t challenge_level) {
    uint16_t health = random_int(1, 5) + challenge_level * 2;

    return (entity) {
        .coins = random_int(5, 15) + challenge_level * 10,
        .base_attack = challenge_level,
        .critical_chance = random_int(5, 10) + challenge_level,
        .current_health = health,
        .defense = random_int(1, 5) + challenge_level,
        .maximum_health = health,
    };
}
