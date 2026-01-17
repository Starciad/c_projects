#include "constants.h"
#include "player.h"

entity player_create(void) {
    return (entity) {
        .base_attack = DEFAULT_PLAYER_BASE_ATTACK,
        .critical_chance = DEFAULT_PLAYER_CRITICAL_CHANCE,
        .current_health = DEFAULT_PLAYER_HEALTH,
        .defense = DEFAULT_PLAYER_DEFENSE,
        .maximum_health = DEFAULT_PLAYER_HEALTH,
    };
}
