#include "enemy.h"
#include "random.h"

entity enemy_create(uint8_t challenge_level) {
    uint8_t health = random_int(1, 10) + challenge_level * 5;

    return (entity) {
        .base_attack = random_int(1, 2) + challenge_level * 2,
        .critical_chance = random_int(5, 10) + challenge_level * 2,
        .current_health = health,
        .defense = random_int(1, 10) + challenge_level * 2,
        .maximum_health = health,
    };
}
