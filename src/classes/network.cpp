
#include <iostream>
#include <vector>
#include "network.h"

using namespace std;

NeuralNetwork::NeuralNetwork(int i, int o, int l, Layer* la)
{
    ::NeuralNetwork(i, o, l, la, Sigmoid, PReLU);
}

NeuralNetwork::NeuralNetwork(int i, int o, int l, Layer* la, ActivationFunction input_acv_fn, ActivationFunction output_acv_fn)
{
    srand(time(0));

    inputs = new Layer(i, input_acv_fn);
    outputs = new Layer(o, output_acv_fn);

    inner_layers = new Layer*[l+2];
    int j;
    for (j=0; j<l; j++) inner_layers[j] = &(la[j]);

    name_neurons();

    if (l) inner_layers[0]->connect_layer(inputs, 1);
    outputs->connect_layer(inner_layers[l-1], 1);
}

NeuralNetwork::NeuralNetwork(int i, int o, int l, int ln, ActivationFunction af)
{
    srand(time(0));

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

void NeuralNetwork::write(FILE* fp)
{
    std::vector<Neuron*> all_neurons;

    // Input layer
    int n = inputs->count_neurons();
    Neuron* neu;
    fwrite(&n, sizeof(int), 1, fp);
    int i;
    for (i=0; i<n; i++)
    {
        neu = inputs->get_neuron(i);
        all_neurons.push_back(neu);
        neu->write(fp);
    }

    // Inner layers
    int m = get_num_layers();
    fwrite(&m, sizeof(int), 1, fp);
    int j;
    for (j=0; j<m; j++)
    {
        n = inner_layers[j]->count_neurons();
        fwrite(&n, sizeof(int), 1, fp);

        for (i=0; i<n; i++)
        {
            neu = inner_layers[j]->get_neuron(i);
            all_neurons.push_back(neu);
            neu->write(fp);
        }
    }

    // Output layer
    n = outputs->count_neurons();
    fwrite(&n, sizeof(int), 1, fp);
    for (i=0; i<n; i++)
    {
        neu = outputs->get_neuron(i);
        all_neurons.push_back(neu);
        neu->write(fp);
    }

    // Connections
    n = all_neurons.size();
    for (i=0; i<n; i++)
    {
        neu = all_neurons[i];
        int s = neu->name.size();

        m = neu->get_num_inputs();
        for (j=0; j<m; j++)
        {
            fwrite(&s, sizeof(int), 1, fp);
            fwrite(neu->name.c_str(), sizeof(char), s, fp);

            const Connection* c = neu->get_input(j);
            fwrite(&(c->multiplier), sizeof(float), 1, fp);

            int z = c->output_from->name.size();
            fwrite(&z, sizeof(int), 1, fp);
            fwrite(c->output_from->name.c_str(), sizeof(char), z, fp);
        }
    }

    n = eof_magic;
    fwrite(&n, sizeof(int), 1, fp);
}

NeuralNetwork* NeuralNetwork::read(FILE* fp)
{
    if (!fp) throw 0xbadf11e;
    NeuralNetwork* result = new NeuralNetwork(0, 0, 0, nullptr);
    
    std::vector<Neuron*> all_neurons;

    // Input layer
    int n;
    Neuron* neu;
    fread(&n, sizeof(int), 1, fp);
    result->inputs = new Layer(n, Identity);
    int i;
    for (i=0; i<n; i++)
    {
        neu = result->inputs->get_neuron(i);
        neu->read(fp);
        all_neurons.push_back(neu);
    }

    // Inner layers
    int m;
    fread(&m, sizeof(int), 1, fp);
    result->inner_layers = new Layer*[m+2];
    int j;
    for (j=0; j<m; j++)
    {
        fread(&n, sizeof(int), 1, fp);

        Layer* layer = new Layer(n, Identity);
        result->inner_layers[j] = layer;

        for (i=0; i<n; i++)
        {
            neu = result->inner_layers[j]->get_neuron(i);
            all_neurons.push_back(neu);
            neu->read(fp);
        }
    }

    // Output layer
    fread(&n, sizeof(int), 1, fp);
    result->outputs = new Layer(n, Identity);
    for (i=0; i<n; i++)
    {
        neu = result->outputs->get_neuron(i);
        neu->read(fp);
        all_neurons.push_back(neu);
    }

    // Connections
    n = all_neurons.size();
    while (!feof(fp))
    {
        int s;
        char buffer[256];
        fread (&s, sizeof(int), 1, fp);
        if (s == eof_magic) break;

        fread(buffer, sizeof(char), s, fp);
        buffer[s] = 0;

        for (i=0; i<n; i++) if (all_neurons[i]->name == (std::string)buffer) break;
        if (i >= n) throw 0xbadda7a;

        float f;
        fread(&f, sizeof(float), 1, fp);

        fread (&s, sizeof(int), 1, fp);
        fread(buffer, sizeof(char), s, fp);
        buffer[s] = 0;

        for (j=0; j<n; j++) if (all_neurons[j]->name == (std::string)buffer) break;
        if (j >= n) throw 0xbadda7a;

        s = all_neurons[i]->get_num_inputs();
        int k;
        for (k=0; k<s; k++) if (all_neurons[i]->get_input(k)->output_from->name == (std::string)buffer) break;
        if (k >= s) all_neurons[i]->attach_input(all_neurons[j]);
        all_neurons[i]->get_input(k)->multiplier = f;
    }

    return result;
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

float NeuralNetwork::train(std::vector<float> viv, int coi)
{
    int s = viv.size();
    float iv[s + 2];
    int i;
    for (i=0; i<s; i++) iv[i] = viv[i];
    iv[s] = 0;
    return train(iv, coi);
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
    if (frand(0,1) > -0.25) return goodness;

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
    float average = 0;
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

        average += f/ic;
    }
    // cout << endl;

    confidence = (greatest-average) / greatest;

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