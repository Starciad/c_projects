#include "enemy.h"
#include "random.h"

entity enemy_create(uint8_t challenge_level) {
    uint8_t health = random_int(1, 10) + challenge_level * 5;

    return (entity) {
        .current_health = health,
        .defense = random_int(1, 10) + challenge_level * 2,
        .maximum_health = health,
    };
}
