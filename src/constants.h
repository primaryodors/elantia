
#ifndef _constants
#define _constants

#include <math.h>

#define rate_cutoff 0.333

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