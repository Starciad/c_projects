#include <stdlib.h>
#include "random.h"

// Generates a random integer between min and max (inclusive)
int32_t random_int(int32_t min, int32_t max)
{
    return min + rand() % (max - min + 1);
}
