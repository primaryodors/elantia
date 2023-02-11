
#include <iostream>
#include "network.h"

using namespace std;

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

    name_neurons();

    inner_layers[0]->connect_layer(inputs, 1);
    outputs->connect_layer(inner_layers[l-1], 1);
}

NeuralNetwork::NeuralNetwork(int i, int o, int l, int ln, ActivationFunction af)
{
    inputs = new Layer(i, PReLU);
    outputs = new Layer(o, PReLU);

    inner_layers = new Layer*[l+2];
    int j;
    for (j=0; j<l; j++)
    {
        inner_layers[j] = new Layer(ln, af);
    }

    name_neurons();
    for (j=0; j<l; j++)
    {
        if (j) inner_layers[j]->connect_layer(inner_layers[j-1], 0.75);
    }

    inner_layers[0]->connect_layer(inputs, 1);
    outputs->connect_layer(inner_layers[l-1], 1);
}

void NeuralNetwork::name_neurons()
{
    int i, j;

    int ic = inputs->count_neurons();
    for (i=0; i<ic; i++) inputs->get_neuron(i)->name = (std::string)"i:" + std::to_string(i+1);

    for (j=0; inner_layers[j]; j++)
    {
        ic = inner_layers[j]->count_neurons();
        for (i=0; i<ic; i++) 
            inner_layers[j]->get_neuron(i)->name = (std::string)"l" + std::to_string(j+1) + (std::string)":" + std::to_string(i+1);
    }

    ic = outputs->count_neurons();
    for (i=0; i<ic; i++) outputs->get_neuron(i)->name = (std::string)"o:" + std::to_string(i+1);
}

float NeuralNetwork::train(float* iv, int coi)
{
    int ic = inputs->count_neurons();
    int i, l, m;

    /*cout << "Training inputs [ ";
    for (i=0; i<ic; i++) cout << iv[i] << " ";
    cout << " ] to output " << coi << endl;*/

    for (i=0; i<ic; i++) inputs->get_neuron(i)->compute_rate_direct(iv[i]);

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
        outputs->get_neuron(i)->forget();
    }

    outputs->get_neuron(coi)->fire_together_wire_together();
    return goodness;

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

    return goodness;
}

int NeuralNetwork::predict(float* iv)
{
    int ic = inputs->count_neurons();
    int i;

    for (i=0; i<ic; i++) inputs->get_neuron(i)->compute_rate_direct(iv[i]);

    for (i=0; inner_layers[i]; i++) inner_layers[i]->compute_all();

    ic = outputs->count_neurons();
    float greatest = 0;
    int result = -1;
    // cout << endl;
    for (i=0; i<ic; i++)
    {
        Neuron* n = outputs->get_neuron(i);
        float f = n->compute_firing_rate();
        // cout << f << " ";
        if (f > greatest)
        {
            greatest = f;
            result = i;
        }
    }
    // cout << endl;

    return result;
}

int NeuralNetwork::get_num_layers()
{
    if (!inner_layers) return 0;
    int i;
    for (i=0; inner_layers[i]; i++); // get count.
    return i;
}

Layer* NeuralNetwork::get_layer(int i)
{
    return inner_layers[i];
}

Layer* NeuralNetwork::get_input_layer()
{
    return inputs;
}

Layer* NeuralNetwork::get_output_layer()
{
    return outputs;
}