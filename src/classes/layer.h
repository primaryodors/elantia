#ifndef _layer
#define _layer

#include "neuron.h"

class Layer
{
    protected:
    Neuron** neurons = nullptr;
    int num_neurons;

    Layer() {;}

    public:
    Layer(int neurons, ActivationFunction active_ftn);
    ~Layer();
    void connect_layer(Layer* previous_layer, float connection_density);
    void compute_all();
    int count_neurons() const;
    Neuron* get_neuron(int index) const;
    Neuron* get_neuron(const char* name) const;
    static Layer* recombine(const Layer* matir, const Layer* atir);
    void mutate();
};



#endif
