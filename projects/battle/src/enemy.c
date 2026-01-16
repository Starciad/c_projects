#include "enemy.h"

enemy enemy_create(uint16_t challenge_level) {
    return (enemy){.health = 80, .defense = 30, .name = "Goblin"};
}

bool enemy_is_alive(const enemy *e) {
    return e->health > 0;
}
