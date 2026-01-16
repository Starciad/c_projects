#include "player.h"

void player_initialize(player *p, char *name) {
    p->health = 100;
    p->defense = 50;
    p->name = name;
}

bool player_is_alive(const player *p) {
    return p->health > 0;
}
