#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include <stdint.h>

typedef struct entity {
    uint8_t current_health;
    uint8_t defense;
    uint8_t maximum_health;
} entity;

extern bool entity_is_alive(const entity *e);

#endif // ENTITY_H