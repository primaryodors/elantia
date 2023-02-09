
#include "neuron.h"

Neuron::Neuron (ActivationFunction af)
{
    acv_fn = af;
    switch (af)
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
        dalpha = frand (-0.5, 0.5);
        break;

        case SELU:
        activation_function = acfn_selu;
        dalpha = frand (-0.5, 0.5);
        dlambda = frand (-0.5, 0.5);
        break;

        case LReLU:
        activation_function = acfn_lrelu;
        break;

        case PReLU:
        activation_function = acfn_prelu;
        dalpha = frand (-0.5, 0.5);
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
    
    return compute_rate_direct(x);
}

float Neuron::compute_rate_direct(float x)
{
    rate = activation_function(x, alpha, lambda);
    return rate;
}

Connection* Neuron::attach_input(Neuron* n)
{
    int i, j;
    if (!inputs) inputs = new Connection[10];
    else
    {
        for (i=0; inputs[i].input_to == this; i++);         // Get count.
        if (!(i%10))
        {
            Connection* temp = new Connection[i+10];
            for (j=0; j<i; j++) temp[j] = inputs[j];
            delete[] inputs;
            inputs = temp;
        }
        inputs[i].output_from = n;
        inputs[i].multiplier = frand(-1, 1);
        inputs[i].input_to = this;
    }
}