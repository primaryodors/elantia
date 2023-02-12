
#ifndef _constants
#define _constants

#include <math.h>

#define rate_cutoff 0.333
#define eof_magic 0xe9da1f1e

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