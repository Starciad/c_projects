#include <stdlib.h>
#include "random.h"

int16_t random_int(int16_t min, int16_t max)
{
    return min + rand() % (max - min + 1);
}
