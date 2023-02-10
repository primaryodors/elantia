#ifndef _network
#define _network

#include "layer.h"

class NeuralNetwork
{
    protected:
    Layer* inputs = nullptr;
    Layer* outputs = nullptr;
    Layer** inner_layers = nullptr;

    void name_neurons();

    public:
    NeuralNetwork(int inputs, int outputs, int layers, Layer* layer_array);
    NeuralNetwork(int inputs, int outputs, int layers, Layer* layer_array, ActivationFunction input_acv_fn, ActivationFunction output_acv_fn);
    NeuralNetwork(int inputs, int outputs, int layers, int layer_neurons, ActivationFunction activation);

    float train(float* input_values, int correct_output_idx);
    int predict(float* input_values);
};




#endif