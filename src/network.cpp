
#include "network.h"

NeuralNetwork::NeuralNetwork(int i, int o, int l, Layer* la)
{
    ::NeuralNetwork(i, o, l, la, Sigmoid, PReLU);
}

NeuralNetwork::NeuralNetwork(int i, int o, int l, Layer* la, ActivationFunction input_acv_fn, ActivationFunction output_acv_fn)
{
    inputs = new Layer(i, input_acv_fn);
    outputs = new Layer(o, output_acv_fn);

    inner_layers = new Layer*[l+2];
    int j;
    for (j=0; j<l; j++) inner_layers[j] = &(la[j]);

    inner_layers[0]->connect_layer(inputs, 1);
    outputs->connect_layer(inner_layers[l-1], 1);
}

NeuralNetwork::NeuralNetwork(int i, int o, int l, int ln, ActivationFunction af)
{
    inputs = new Layer(i, Sigmoid);
    outputs = new Layer(o, PReLU);

    inner_layers = new Layer*[l+2];
    int j;
    for (j=0; j<l; j++) inner_layers[j] = new Layer(ln, af);

    inner_layers[0]->connect_layer(inputs, 1);
    outputs->connect_layer(inner_layers[l-1], 1);
}

void NeuralNetwork::train(float* iv, int coi)
{
    int ic = inputs->count_neurons();
    int i, l, m;

    for (i=0; i<ic; i++) inputs->get_neuron(i)->compute_rate_direct(iv[i]);

    inputs->compute_all();
    for (i=0; inner_layers[i]; i++) inner_layers[i]->compute_all();

    ic = outputs->count_neurons();
    float outvals[ic];
    for (i=0; i<ic; i++)
    {
        Neuron* n = outputs->get_neuron(i);
        float f = n->compute_firing_rate();
        outvals[i] = f;
    }

    float goodness = outvals[coi];

    for (i=0; i<ic; i++)
    {
        if (i == coi) continue;
        goodness -= outvals[i];
    }

    for (l=0; inner_layers[l]; l++)
    {
        int nc = inner_layers[l]->count_neurons();
        for (m=0; m<nc; m++)
        {
            Neuron* n = inner_layers[l]->get_neuron(m);

            n->tweak_something();

            for (i=0; i<ic; i++)
            {
                float f = outputs->get_neuron(i)->compute_firing_rate();
                outvals[i] = f;
            }

            float new_goodness = outvals[coi];

            for (i=0; i<ic; i++)
            {
                if (i == coi) continue;
                new_goodness -= outvals[i];
            }

            if (new_goodness >= goodness)
            {
                goodness = new_goodness;
            }
            else
            {
                n->put_it_back();
            }
        }
    }
}

int NeuralNetwork::predict(float* iv)
{
    int ic = inputs->count_neurons();
    int i;

    for (i=0; i<ic; i++) inputs->get_neuron(i)->compute_rate_direct(iv[i]);

    inputs->compute_all();
    for (i=0; inner_layers[i]; i++) inner_layers[i]->compute_all();

    ic = outputs->count_neurons();
    float greatest = 0;
    int result = -1;
    for (i=0; i<ic; i++)
    {
        Neuron* n = outputs->get_neuron(i);
        float f = n->compute_firing_rate();
        if (f > greatest)
        {
            greatest = f;
            result = i;
        }
    }

    return result;
}