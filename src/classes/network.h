#ifndef _network
#define _network

#include "layer.h"

class NeuralNetwork
{
    protected:
    Layer* inputs = nullptr;
    Layer* outputs = nullptr;
    Layer** inner_layers = nullptr;

    float confidence = 0;

    void name_neurons();

    public:
    // Constructors
    NeuralNetwork(int inputs, int outputs, int layers, Layer* layer_array);
    NeuralNetwork(int inputs, int outputs, int layers, Layer* layer_array, ActivationFunction input_acv_fn, ActivationFunction output_acv_fn);
    NeuralNetwork(int inputs, int outputs, int layers, int layer_neurons, ActivationFunction activation);

    // Serialization
    void write(FILE* pfile);
    static NeuralNetwork* read(FILE* pfile);

    // Layer ftns
    int get_num_layers();
    Layer* get_layer(int index);
    Layer* get_input_layer();
    Layer* get_output_layer();

    // Learning and predicting
    float train(float* input_values, int correct_output_idx);
    float train(std::vector<float> input_values, int correct_output_idx);
    int predict(float* input_values);
    float get_confidence() { return confidence; }
};




#endif