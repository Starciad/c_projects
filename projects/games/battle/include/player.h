#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct player {
    uint32_t defense;
    uint32_t health;
    char *name;
} player;

extern void player_initialize(player *p, char *name);
extern bool player_is_alive(const player *p);

#endif // PLAYER_H