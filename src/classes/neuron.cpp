
#include <iostream>
#include "neuron.h"

using namespace std;

Neuron::Neuron (ActivationFunction af)
{
    acv_fn = af;
    switch (af)
    {
        case Identity:
        activation_function = acfn_identity;
        break;

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
        dalpha = frand(-0.05, 0.05);
        alpha = 1;
        break;

        case SELU:
        activation_function = acfn_selu;
        dalpha = frand(-0.05, 0.05);
        dlambda = frand(-0.05, 0.05);
        alpha = 1.67;
        break;

        case LReLU:
        activation_function = acfn_lrelu;
        break;

        case PReLU:
        activation_function = acfn_prelu;
        dalpha = frand(-0.05, 0.05);
        alpha = 0.7;
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

Neuron::~Neuron()
{
    if (inputs) delete inputs;
}

Neuron* Neuron::recombine(const Neuron* matir, const Neuron* atir)
{
    Neuron* result = new Neuron();
    const Neuron* parent = (rand() & 1) ? matir : atir;
    result->activation_function = parent->activation_function;
    result->acv_fn = parent->acv_fn;

    float f = frand(0,1);
    float f1 = 1.0 - f;
    result->alpha = f * matir->alpha + f1 * atir->alpha;

    f = frand(0,1);
    f1 = 1.0 - f;
    result->color.red   = f * matir->color.red   + f1 * atir->color.red;
    result->color.green = f * matir->color.green + f1 * atir->color.green;
    result->color.blue  = f * matir->color.blue  + f1 * atir->color.blue;

    result->dalpha  = frand(-0.1, 0.1);
    result->dlambda = frand(-0.1, 0.1);

    f = frand(0,1);
    f1 = 1.0 - f;
    result->lambda = f * matir->lambda + f1 * atir->lambda;

    return result;
}

void Neuron::write(FILE* fp)
{
    fwrite(&version, sizeof(int), 1, fp);
    fwrite(&acv_fn, sizeof(ActivationFunction), 1, fp);
    fwrite(&alpha, sizeof(float), 1, fp);
    fwrite(&lambda, sizeof(float), 1, fp);

    int l = name.size();
    fwrite(&l, sizeof(int), 1, fp);
    if (l) fwrite(name.c_str(), sizeof(char), l, fp);

    fwrite(&color, sizeof(Color), 1, fp);
}

void Neuron::read(FILE* fp)
{
    int lversion;
    fread(&lversion, sizeof(int), 1, fp);

    if (lversion > version) throw 0x200900;     // Too new: file was made by a newer version of the app.

    if (lversion >= 1)
    {
        fread(&acv_fn, sizeof(ActivationFunction), 1, fp);
        fread(&alpha, sizeof(float), 1, fp);
        fread(&lambda, sizeof(float), 1, fp);

        int l = 0;
        fread(&l, sizeof(int), 1, fp);
        if (l)
        {
            char buffer[l+4];
            fread(buffer, sizeof(char), l, fp);
            buffer[l] = 0;

            name = (std::string)buffer;
        }

        fread(&color, sizeof(Color), 1, fp);
    }
}

float Neuron::compute_firing_rate()
{
    float x = 0;

    // Sum inputs.
    if (inputs)
    {
        int i;
        for (i=0; inputs[i].input_to == this; i++)
            x += (inputs[i].output_from->rate * inputs[i].multiplier);
        
        /*if (fabs(x) > 0.9)
        {
            for (i=0; inputs[i].input_to == this; i++) inputs[i].multiplier *= 0.99;
        }
        else if (x < 0.1)
        {
            for (i=0; inputs[i].input_to == this; i++) inputs[i].multiplier += frand(0, 0.1);
        }*/
    }

    return compute_rate_direct(x);
}

float Neuron::compute_rate_direct(float x)
{
    rate = activation_function(x, alpha, lambda);
    if (rate < -0.5) rate = -0.5;
    if (rate > 1) rate = 1;
    return rate;
}

Connection* Neuron::attach_input(Neuron* n)
{
    int i=0, j;
    if (!inputs) inputs = new Connection[10];
    else
    {
        for (i=0; inputs[i].input_to == this; i++);         // Get count.
        if (!(i%10))
        {
            Connection* temp = new Connection[i+10];
            for (j=0; j<i; j++) temp[j] = inputs[j];
            delete inputs;
            inputs = temp;
        }
    }
    inputs[i].output_from = n;
    inputs[i].multiplier = frand(-0.5, 1);
    inputs[i].input_to = this;

    // cout << inputs[i].output_from->name << " -> " << inputs[i].input_to->name << " (" << inputs[i].multiplier << ")" << endl;

    return &(inputs[i]);
}

void Neuron::tweak_something()
{
    if (!inputs) return;
    int tweak = rand() % (dlambda ? 3 : (dalpha ? 2 : 1));
    switch (tweak)
    {
        case 0:
        int i, j;
        for (i=0; inputs[i].input_to == this; i++);         // Get count;
        j = rand() % i;
        last_tweaked = j + 10000;
        last_tweaked_value = inputs[j].multiplier;
        inputs[j].multiplier += inputs[j].dmult;
        if (inputs[j].multiplier > 1) inputs[j].multiplier = 1;
        if (inputs[j].multiplier < -1) inputs[j].multiplier = -1;
        break;

        case 1:
        last_tweaked = tweak;
        last_tweaked_value = alpha;
        alpha += dalpha;
        break;

        case 2:
        last_tweaked = tweak;
        last_tweaked_value = lambda;
        lambda += dlambda;
        break;

        default:
        ;
    }
}

void Neuron::put_it_back()
{
    if (!inputs) return;
    if (last_tweaked >= 10000)
    {
        int j = last_tweaked - 10000;
        inputs[j].multiplier = last_tweaked_value;
        inputs[j].dmult *= -0.666;
    }
    else switch (last_tweaked)
    {
        case 1:
        alpha = last_tweaked_value;
        dalpha *= -0.9;
        break;

        case 2:
        lambda = last_tweaked_value;
        dlambda *= -0.9;
        break;

        default:
        ;
    }
}

void Neuron::equalize_inputs()
{
    if (!inputs) return;

    int i;
    float tmp = 0, tmm = 0;
    for (i=0; inputs[i].input_to == this; i++)
    {
        if (inputs[i].multiplier >= 0) tmp += inputs[i].multiplier;
        else tmm += fabs(inputs[i].multiplier);
    }

    if (tmp)
    {
        tmp = 1.0/tmp;
        for (i=0; inputs[i].input_to == this; i++) if (inputs[i].multiplier > 0) inputs[i].multiplier *= tmp;
    }

    if (tmm)
    {
        tmm = 0.666/fabs(tmm);
        for (i=0; inputs[i].input_to == this; i++) if (inputs[i].multiplier < 0) inputs[i].multiplier *= tmm;
    }
}

void Neuron::fire_together_wire_together()
{
    if (!inputs) return;

    int i;
    for (i=0; inputs[i].input_to == this; i++)
    {
        if (rate < rate_cutoff) inputs[i].multiplier += inputs[i].output_from->rate;
        if (inputs[i].output_from->rate >= rate_cutoff) inputs[i].output_from->fire_together_wire_together();
    }

    equalize_inputs();
}

void Neuron::forget()
{
    return;
    if (!inputs) return;

    int i;
    for (i=0; inputs[i].input_to == this; i++)
    {
        if (rate > rate_cutoff) inputs[i].multiplier -= inputs[i].output_from->rate;
        if (inputs[i].output_from->rate < rate_cutoff) inputs[i].output_from->forget();
    }

    equalize_inputs();
}

int Neuron::get_num_inputs()
{
    if (!inputs) return 0;
    int i;
    for (i=0; inputs[i].input_to == this; i++);         // Get count.
    return i;
}

Connection* Neuron::get_input(int i)
{
    if (!inputs) return 0;
    return &(inputs[i]);
}