#include "constants.h"
#include "item.h"
#include "random.h"

const char* item_get_name(const item_type type) {
    switch (type) {
        case ITEM_TYPE_HEALTH_POTION:
            return ITEM_HEALTH_POTION_NAME;
        case ITEM_TYPE_MANA_POTION:
            return ITEM_MANA_POTION_NAME;
        default:
            return ITEM_UNKNOWN_NAME;
    }
}

item_type item_get_random(void) {
    return (item_type)(random_int(0, ITEM_TYPE_LENGTH - 1));
}