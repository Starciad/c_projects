#include "entity.h"

bool entity_is_alive(const entity *e) {
    return e->current_health > 0;
}
