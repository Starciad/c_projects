#ifndef PLAYER_H
#define PLAYER_H

typedef struct player {
    uint32_t defense;
    uint32_t health;
    char *name;
} player;

extern void player_initialize(player *p, char *name);

#endif // PLAYER_H