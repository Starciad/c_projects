#include "constants.h"
#include "player.h"

entity player_create(void) {
    return (entity) {
        .current_health = DEFAULT_PLAYER_HEALTH,
        .defense = DEFAULT_PLAYER_DEFENSE,
        .maximum_health = DEFAULT_PLAYER_HEALTH,
    };
}
