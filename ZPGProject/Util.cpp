#include "Util.h"
#include <stdlib.h>

int Util::getRandomInt(int start, int end)
{
    return rand() % (end - start + 1) + start;
}

float Util::getRandomFloat(float start, float end)
{
    int randomInt = rand();
    return start + (float)(randomInt) / RAND_MAX * (end - start);
}
