
#ifndef _neuron
#define _neuron

#include <stdio.h>
#include <string>
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

    float dalpha = 0;
    float dlambda = 0;
    int last_tweaked = 0;
    float last_tweaked_value = 0;

    void equalize_inputs();

    public:
    // Constructor and Initialization
    Neuron (ActivationFunction acv_function);
    Connection* attach_input(Neuron* n);
    std::string name;

    // Serialization
    void write(FILE* pfile);
    void read(FILE* pfile);

    // Prediction
    float compute_firing_rate();
    float compute_rate_direct(float input);

    // Learning
    void tweak_something();
    void put_it_back();
    void fire_together_wire_together();             // Strengthen positive inputs.
    void forget();                                  // Weaken positive inputs.
};

struct Connection
{
    Neuron* output_from = nullptr;
    Neuron* input_to = nullptr;
    float multiplier = 0;
    float dmult = frand(-0.5, 0.5);
};

#endif

