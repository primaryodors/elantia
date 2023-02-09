#ifndef _layer
#define _layer

#include "neuron.h"

class Layer
{
    protected:
    Neuron** neurons = nullptr;
    int num_neurons;

    public:
    Layer(int neurons, ActivationFunction active_ftn);
    void connect_layer(Layer* previous_layer, float connection_density);
    void compute_all();
    int count_neurons();
    Neuron* get_neuron(int index);
};



#endif
