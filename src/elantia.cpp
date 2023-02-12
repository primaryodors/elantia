
#include <iostream>
#include <chrono>
#include <thread>
#include <sys/time.h>
#include <string.h>
#include <vector>
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
    else if (!strcmp(argv[1], "train"))
    {
        if (argc < 4) return -1;
        int iters = 10000;

        for (i=3; i<argc; i++)
        {
            if (!strcmp("--iter", argv[i]))
            {
                i++;
                iters = atoi(argv[i]);
            }
        }

        FILE* fp = fopen(argv[2], "rb");
        if (!fp) return -2;
        NeuralNetwork* neur = NeuralNetwork::read(fp);
        fclose(fp);

        fp = fopen(argv[3], "rb");
        if (!fp) return -3;
        std::vector<int> train_outs;
        std::vector<std::vector<float>> train_ins;

        char buffer[1024];
        while (!feof(fp))
        {
            if (!fgets(buffer, 1020, fp)) break;
            for (i=0; buffer[i]; i++) if (buffer[i] == ':') break;
            if (buffer[i])
            {
                buffer[i] = 0;
                j = atoi(buffer);
                train_outs.push_back(j);

                l = i+1;
                std::vector<float> instemp;
                for (k=l; buffer[k] == ' '; k++);
                for (; buffer[k]; k++)
                {
                    if (buffer[k] == ' ')
                    {
                        buffer[k] = 0;
                        float f = atof(&(buffer[l]));
                        instemp.push_back(f);
                        for (l=k+1; buffer[l] == ' '; l++);
                        k = l;
                    }
                }

                train_ins.push_back(instemp);
            }
        }

        // Debug step
        k = train_outs.size();
        for (i=0; i<k; i++)
        {
            cout << "Output " << train_outs[i] << " for ";
            l = train_ins[i].size();
            for (j=0; j<l; j++)
            {
                if (j) cout << ", ";
                cout << train_ins[i][j];
            }
            cout << "." << endl;
        }
        cout << endl;

        for (i=0; i<iters; i++)
        {
            cout << "Training iteration " << i << "...                      " << endl << "\x1b[A";
            for (j=0; j<k; j++)
            {
                neur->train(train_ins[j], train_outs[j]);
            }
        }

        cout << endl << endl;

        FILE* fp = fopen(argv[2], "wb");
        if (!fp) return -2;
        neur->write(fp);
        fclose(fp);
    }

    return 0;
}