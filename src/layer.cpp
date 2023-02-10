
#include "layer.h"
#include <math.h>
#include <iostream>

using namespace std;

Layer::Layer(int n, ActivationFunction af)
{
    num_neurons = n;
    neurons = new Neuron*[n+2];
    int i;
    for (i=0; i<n; i++) neurons[i] = new Neuron(af);
    neurons[n] = nullptr;
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

int Layer::count_neurons()
{
    return num_neurons;
}

Neuron* Layer::get_neuron(int index)
{
    return neurons[index];
}