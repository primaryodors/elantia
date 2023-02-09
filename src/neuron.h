
#ifndef _neuron
#define _neuron

#include "constants.h"
#include "activation.h"

struct Connection;

class Neuron
{
    protected:
    Connection* inputs = nullptr;
    ActivationFunction acv_fn;
    float (*activation_function)(float, float, float) = nullptr;
    float alpha = 1;            // Not used by all types.
    float lambda = 1;           // "
    float rate = 0;

    public:
    Neuron (ActivationFunction acv_function);
    float compute_firing_rate();
    float compute_rate_direct(float input);
    Connection* attach_input(Neuron* n);
};

struct Connection
{
    Neuron* output_from = nullptr;
    Neuron* input_to = nullptr;
    float multiplier = 0;
};




#endif
