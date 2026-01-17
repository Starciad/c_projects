#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include <stdint.h>

typedef struct entity {
    uint32_t coins;
    uint16_t base_attack;
    uint16_t critical_chance;
    uint16_t current_health;
    uint16_t defense;
    uint16_t maximum_health;
    bool is_defending;
    bool is_preparing_attack;
} entity;

typedef enum entity_attack_value_type {
    ENTITY_ATTACK_VALUE_MINIMUM = 0,
    ENTITY_ATTACK_VALUE_MAXIMUM = 1,
    ENTITY_ATTACK_VALUE_RANDOM = 2,
    ENTITY_ATTACK_VALUE_CRITICAL_HIT = 3,
    ENTITY_ATTACK_VALUE_POWERFUL = 4,
} entity_attack_value_type;

extern bool entity_is_alive(const entity *e);
extern uint16_t entity_get_attack_value(const entity *e, const entity_attack_value_type type);
extern bool entity_is_critical_hit(const entity *e);
extern uint16_t entity_take_damage(entity *e, const uint16_t damage);

#endif // ENTITY_H