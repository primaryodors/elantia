
#ifndef _constants
#define _constants

#include <math.h>

enum ActivationFunction
{
    // https://en.wikipedia.org/wiki/Activation_function
    Identity,
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

float frand(float lmin, float lmax);

#endif