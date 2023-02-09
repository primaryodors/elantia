
#include "constants.h"
#include "activation.h"
#include <math.h>

float acfn_sigmoid( float x, float alpha, float lambda)
{
    return 1.0 / (1.0 + exp(-x));
}

float acfn_tanh(    float x, float alpha, float lambda)
{
    return tanh(x);
}

float acfn_relu(    float x, float alpha, float lambda)
{
    if (x <= 0) return 0;
    else return x;
}

float acfn_gelu(    float x, float alpha, float lambda)
{
    // TODO: Find out what "erf" means.
    // https://en.wikipedia.org/wiki/Activation_function
}

float acfn_softplus(float x, float alpha, float lambda)
{
    return log(1.0 + exp(x));
}

float acfn_elu(     float x, float alpha, float lambda)
{
    if (x <= 0) return alpha * (exp(x)-1);
    else return x;
}

float acfn_selu(    float x, float alpha, float lambda)
{
    return lambda*acfn_elu(x, alpha, lambda);
}

float acfn_lrelu(   float x, float alpha, float lambda)
{
    if (x<0) return 0.01*lambda*x;
    else return x;
}

float acfn_prelu(   float x, float alpha, float lambda)
{
    if (x <= 0) return alpha * x;
    else return x;
}

float acfn_silu(    float x, float alpha, float lambda)
{
    return x / (1.0 + exp(-x));
}

float acfn_gaussian(float x, float alpha, float lambda)
{
    return exp(-(x*x));
}



