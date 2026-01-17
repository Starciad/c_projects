#include "enemy.h"
#include "random.h"

entity enemy_create(uint16_t challenge_level) {
    uint16_t health = random_int(1, 5) + challenge_level * 2;

    return (entity) {
        .coins = (challenge_level * 10) + random_int(5, 15),
        .base_attack = challenge_level,
        .critical_chance = challenge_level + random_int(5, 10),
        .current_health = health,
        .defense = challenge_level + random_int(0, 2),
        .maximum_health = health,
        .is_defending = false,
        .is_preparing_attack = false,
    };
}
