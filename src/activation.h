
#ifndef _activation
#define _activation

// Even though not all functions use alpha or lambda, our function pointer call must send the same params no matter what for maximum performance.
float acfn_sigmoid( float x, float alpha, float lambda);
float acfn_tanh(    float x, float alpha, float lambda);
float acfn_relu(    float x, float alpha, float lambda);
float acfn_gelu(    float x, float alpha, float lambda);
float acfn_softplus(float x, float alpha, float lambda);
float acfn_elu(     float x, float alpha, float lambda);
float acfn_selu(    float x, float alpha, float lambda);
float acfn_lrelu(   float x, float alpha, float lambda);
float acfn_prelu(   float x, float alpha, float lambda);
float acfn_silu(    float x, float alpha, float lambda);
float acfn_gaussian(float x, float alpha, float lambda);

#endif
