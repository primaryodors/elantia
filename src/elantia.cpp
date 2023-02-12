
#include <iostream>
#include <chrono>
#include <thread>
#include <sys/time.h>
#include <string.h>
#include "classes/network.h"

using namespace std;

int main (int argc, char** argv)
{
    if (argc < 2) return -1;
    int i, j, k, l;

    if (!strcmp(argv[1], "create"))
    {
        if (argc < 3) return -1;

        int inputs = 3, outputs = 10, layers = 2, neurons = 50;
        ActivationFunction acvftn = SELU;

        for (i=3; i<argc; i++)
        {
            if (!strcmp("--inputs", argv[i]))
            {
                i++;
                inputs = atoi(argv[i]);
            }
            else if (!strcmp("--outputs", argv[i]))
            {
                i++;
                outputs = atoi(argv[i]);
            }
            else if (!strcmp("--layers", argv[i]))
            {
                i++;
                layers = atoi(argv[i]);
            }
            else if (!strcmp("--function", argv[i]))
            {
                i++;
                if (!strcmp("Identity", argv[i])) acvftn = Identity;
                else if (!strcmp("Sigmoid", argv[i])) acvftn = Sigmoid;
                else if (!strcmp("Hyperbolic", argv[i])) acvftn = Hyperbolic;
                else if (!strcmp("ReLU", argv[i])) acvftn = ReLU;
                else if (!strcmp("GELU", argv[i])) acvftn = GELU;
                else if (!strcmp("Softplus", argv[i])) acvftn = Softplus;
                else if (!strcmp("ELU", argv[i])) acvftn = ELU;
                else if (!strcmp("SELU", argv[i])) acvftn = SELU;
                else if (!strcmp("LReLU", argv[i])) acvftn = LReLU;
                else if (!strcmp("PReLU", argv[i])) acvftn = PReLU;
                else if (!strcmp("SiLU", argv[i])) acvftn = SiLU;
                else if (!strcmp("Gaussian", argv[i])) acvftn = Gaussian;
                else return -3;
            }
        }

        NeuralNetwork neur(inputs, outputs, layers, neurons, acvftn);

        FILE* fp = fopen(argv[2], "wb");
        if (!fp) return -2;
        neur.write(fp);
        fclose(fp);
    }

    return 0;
}