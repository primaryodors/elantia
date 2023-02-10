
#include "constants.h"

float frand(float lmin, float lmax)
{
    int r = rand();
    float f = (float)r / RAND_MAX;
    f *= (lmax-lmin);
    return f+lmin;
}

