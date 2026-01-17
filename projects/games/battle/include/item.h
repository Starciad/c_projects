#ifndef ITEM_H
#define ITEM_H

#include "entity.h"

typedef enum item {
    ITEM_HEALTH_POTION,
    ITEM_MANA_POTION,
    ITEM_LENGTH
} item;

extern const char* item_get_name(const item type);
extern item item_get_random(void);

#endif // ITEM_H