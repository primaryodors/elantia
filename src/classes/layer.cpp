
#include "layer.h"
#include <math.h>
#include <iostream>
#include <string.h>

using namespace std;

Layer::Layer(int n, ActivationFunction af)
{
    num_neurons = n;
    neurons = new Neuron*[n+2];
    int i;
    for (i=0; i<n; i++) neurons[i] = new Neuron(af);
    neurons[n] = nullptr;
}

Layer::~Layer()
{
    if (neurons) delete[] neurons;
}

Layer* Layer::recombine(const Layer* matir, const Layer* atir)
{
    if (matir->num_neurons != atir->num_neurons) throw 0xbadb019c;
    Layer* result = new Layer();
    result->num_neurons = matir->num_neurons;
    result->neurons = new Neuron*[result->num_neurons+2];
    int i;
    for (i=0; i<result->num_neurons; i++) result->neurons[i] = Neuron::recombine(matir->neurons[i], atir->neurons[i]);
    return result;
}

void Layer::mutate()
{
    if (!neurons) return;
    int i;
    for (i=0; i<num_neurons; i++)
    {
        neurons[i]->mutate();
    }
}

void Layer::connect_layer(Layer* prev, float cd)
{
    if (cd < 0 || cd > 1) throw 0xbadcd;

    int i, j;
    float f;

    for (i=0; i<num_neurons; i++)
    {
        for (j=0; j<prev->num_neurons; j++)
        {
            f = frand(0,1);
            if (f <= cd)
            {
                neurons[i]->attach_input(prev->neurons[j]);
            }
        }
        // cout << "A neuron has been attached to " << neurons[i]->get_num_inputs() << " other neurons with density " << cd << endl;
    }
}

void Layer::compute_all()
{
    int i;
    for (i=0; i<num_neurons; i++)
    {
        float f = neurons[i]->compute_firing_rate();
        // cout << neurons[i]->name << " = " << f << "; ";
    }
    // cout << endl;
}

int Layer::count_neurons() const
{
    return num_neurons;
}

Neuron* Layer::get_neuron(int i) const
{
    if (i<0 || i>num_neurons) return nullptr;
    return neurons[i];
}

Neuron* Layer::get_neuron(const char* name) const
{
    if (!neurons) return nullptr;
    int i;
    for (i=0; i<num_neurons; i++)
    {
        if (!strcmp(name, neurons[i]->name.c_str())) return neurons[i];
    }

    return nullptr;
}