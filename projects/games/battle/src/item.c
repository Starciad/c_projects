#include <stdio.h>
#include "item.h"
#include "random.h"

static const char* ITEM_NONE_NAME = "(Empty Slot)";
static const char* ITEM_HEALTH_POTION_NAME = "Health Potion";
static const char* ITEM_MANA_POTION_NAME = "Mana Potion";
static const char* ITEM_UNKNOWN_NAME = "Unknown Item";

static const char* ITEM_NONE_DESCRIPTION = "An empty slot. No item is present.";
static const char* ITEM_HEALTH_POTION_DESCRIPTION = "A potion that restores 20 health points when used.";
static const char* ITEM_MANA_POTION_DESCRIPTION = "A potion that restores 15 mana points when used.";
static const char* ITEM_UNKNOWN_DESCRIPTION = "An unknown item with mysterious properties.";

static const int HEAL_AMOUNT = 20;
static const int MANA_AMOUNT = 15;

const char* item_get_name(const item type) {
    switch (type) {
        case ITEM_NONE:
            return ITEM_NONE_NAME;
        case ITEM_HEALTH_POTION:
            return ITEM_HEALTH_POTION_NAME;
        case ITEM_MANA_POTION:
            return ITEM_MANA_POTION_NAME;
        default:
            return ITEM_UNKNOWN_NAME;
    }
}

const char* item_get_description(const item type) {
    switch (type) {
        case ITEM_NONE:
            return ITEM_NONE_DESCRIPTION;
        case ITEM_HEALTH_POTION:
            return ITEM_HEALTH_POTION_DESCRIPTION;
        case ITEM_MANA_POTION:
            return ITEM_MANA_POTION_DESCRIPTION;
        default:
            return ITEM_UNKNOWN_DESCRIPTION;
    }
}

item item_get_random(void) {
    return (item)(random_int(0, ITEM_LENGTH - 1));
}

void item_use(entity* user, const item it) {
    switch (it) {
        case ITEM_HEALTH_POTION:
        {
            const int actual_heal = entity_heal(user, HEAL_AMOUNT);
            printf("* You used a %s and restored %d health!\n", ITEM_HEALTH_POTION_NAME, actual_heal);
            break;
        }
        case ITEM_MANA_POTION:
        {
            const int actual_mana = entity_restore_mana(user, MANA_AMOUNT);
            printf("* You used a %s and restored %d mana!\n", ITEM_MANA_POTION_NAME, actual_mana);
            break;
        }
        case ITEM_NONE:
        default:
            puts("* There is no item to use!");
            break;
    }
}