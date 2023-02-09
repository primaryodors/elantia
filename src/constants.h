
#ifndef _constants
#define _constants

#include <math.h>

enum ActivationFunction
{
    // https://en.wikipedia.org/wiki/Activation_function
    Sigmoid,
    Hyperbolic,
    ReLU,
    GELU,
    Softplus,
    ELU,
    SELU,
    LReLU,
    PReLU,
    SiLU,
    Gaussian
};

float frand(float lmin, float lmax)
{
    int r = rand();
    float f = (float)r / RAND_MAX;
    f *= (lmax-lmin);
    return f+lmin;
}

#endif