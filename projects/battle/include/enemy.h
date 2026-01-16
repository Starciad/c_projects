#ifndef ENEMY_H
#define ENEMY_H

#include <stdbool.h>
#include <stdint.h>

typedef struct enemy {
    uint32_t defense;
    uint32_t health;
    char *name;
} enemy;

extern enemy enemy_create(uint16_t challenge_level);
extern bool enemy_is_alive(const enemy *e);

#endif // ENEMY_H