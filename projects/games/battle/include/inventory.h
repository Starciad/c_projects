#ifndef INVENTORY_H
#define INVENTORY_H

#include "constants.h"
#include "item.h"

typedef struct inventory {
    item items[INVENTORY_CAPACITY];
} inventory;

#endif // INVENTORY_H