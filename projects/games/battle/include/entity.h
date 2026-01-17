#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include <stdint.h>

typedef struct entity {
    uint8_t base_attack;
    uint8_t critical_chance;
    uint8_t current_health;
    uint8_t defense;
    uint8_t maximum_health;
} entity;

typedef enum entity_attack_value_type {
    ENTITY_ATTACK_VALUE_MINIMUM = 0,
    ENTITY_ATTACK_VALUE_MAXIMUM = 1,
    ENTITY_ATTACK_VALUE_RANDOM = 2,
    ENTITY_ATTACK_VALUE_CRITICAL_HIT = 3
} entity_attack_value_type;

extern bool entity_is_alive(const entity *e);
extern uint8_t entity_get_attack_value(const entity *e, const entity_attack_value_type type);
extern bool entity_is_critical_hit(const entity *e);
extern void entity_take_damage(entity *e, const uint8_t damage);

#endif // ENTITY_H