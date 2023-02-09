
#include "neuron.h"

Neuron::Neuron (NeuralType nt)
{
    type = nt;
    switch (nt)
    {
        case Sigmoid:
        activation_function = acfn_sigmoid;
        break;

        case Hyperbolic:
        activation_function = acfn_tanh;
        break;

        case ReLU:
        activation_function = acfn_relu;
        break;

        case GELU:
        activation_function = acfn_gelu;
        break;

        case Softplus:
        activation_function = acfn_softplus;
        break;

        case ELU:
        activation_function = acfn_elu;
        break;

        case SELU:
        activation_function = acfn_selu;
        break;

        case LReLU:
        activation_function = acfn_lrelu;
        break;

        case PReLU:
        activation_function = acfn_prelu;
        break;

        case SiLU:
        activation_function = acfn_silu;
        break;

        case Gaussian:
        activation_function = acfn_gaussian;
        break;
        
        default:
        ;
    }
}


float Neuron::compute_firing_rate()
{
    float x = 0;

    // Sum inputs.
    int i;
    for (i=0; inputs[i]; i++)
        x += inputs[i]->output_from->rate;

    rate = activation_function(x, alpha, lambda);
    return rate;
}

Connection* Neuron::attach_input(Neuron* n)
{
    // TODO:
}