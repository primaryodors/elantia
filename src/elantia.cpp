
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
            else if (!strcmp("--neurons", argv[i]))
            {
                i++;
                neurons = atoi(argv[i]);
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

                float f = atof(&(buffer[l]));
                instemp.push_back(f);

                train_ins.push_back(instemp);
            }
        }

        k = train_outs.size();

        #if false
        // Debug step
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
        #endif

        for (i=0; i<iters; i++)
        {
            cout << "Training iteration " << i << "...                      " << endl << "\x1b[A" << flush;
            for (j=0; j<k; j++)
            {
                neur->train(train_ins[j], train_outs[j]);
            }
        }

        cout << endl << endl;

        fp = fopen(argv[2], "wb");
        if (!fp) return -2;
        neur->write(fp);
        fclose(fp);
    }
    else if (!strcmp(argv[1], "evolve"))
    {
        // Determine population size, number of generations, and training and evaluation sets.
        int popsz = 10, gener = 10;
        if (argc < 5) return -1;

        if (argc > 5) gener = atoi(argv[5]);
        if (argc > 6) popsz = atoi(argv[6]);
        std::vector<int> train_outs;
        std::vector<std::vector<float>> train_ins;
        std::vector<int> eval_outs;
        std::vector<std::vector<float>> eval_ins;

        FILE* fp;
        char buffer[1024];

        fp = fopen(argv[3], "rb");
        if (!fp) return -3;
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

                float f = atof(&(buffer[l]));
                instemp.push_back(f);

                train_ins.push_back(instemp);
            }
        }

        fp = fopen(argv[4], "rb");
        if (!fp) return -4;
        while (!feof(fp))
        {
            if (!fgets(buffer, 1020, fp)) break;
            for (i=0; buffer[i]; i++) if (buffer[i] == ':') break;
            if (buffer[i])
            {
                buffer[i] = 0;
                j = atoi(buffer);
                eval_outs.push_back(j);

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

                float f = atof(&(buffer[l]));
                instemp.push_back(f);

                eval_ins.push_back(instemp);
            }
        }

        // Load the ai file.
        fp = fopen(argv[2], "rb");
        if (!fp) return -2;
        NeuralNetwork* neur = NeuralNetwork::read(fp);
        fclose(fp);

        // Make copies but mutate the inputs.
        NeuralNetwork* population[popsz];
        int n, g;
        for (i=0; i<popsz; i++)
        {
            population[i] = new NeuralNetwork(*neur);
            population[i]->mutate();
        }

        int mostright=0, secright=0, bestn = -1, secn = -1;
        k = train_ins.size();
        for (g=1; g<=gener; g++)
        {
            // Train and evaluate each copy.
            int iters = 10;                         // TODO: Make this settable.
            mostright = secright = 0;
            bestn = secn = -1;
            for (n=0; n<popsz; n++)
            {
                cout << "Training generation " << g << " individual " << n+1 << "...                      " << endl << "\x1b[A" << flush;
                for (i=0; i<iters; i++)
                {
                    for (j=0; j<k; j++)
                    {
                        population[n]->train(train_ins[j], train_outs[j]);
                    }
                }

                int numright = 0;
                int s = eval_outs.size();
                float input_vals[s];
                for (j=0; j<k; j++)
                {
                    cout << "Evaluate generation " << g << " individual " << n+1 << "...                      " << endl << "\x1b[A" << flush;
                    for (i=0; i<s; i++) input_vals[i] = eval_ins[j][i];
                    int result = population[n]->predict(input_vals);
                    if (result == eval_outs[j]) numright++;
                }

                if (!n || numright > mostright)
                {
                    secright = mostright;
                    secn = bestn;
                    mostright = numright;
                    bestn = n;
                }
                else if (numright > secright)
                {
                    secright = numright;
                    secn = n;
                }
            }

            if (bestn < 0 || secn < 0) throw 0xbadc0de;

            // Breed the two best results to get the next generation.
            // Repeat from the train and evaluate step until number of generations.
            if (g == gener) break;

            NeuralNetwork* nextgen[popsz];
            for (i=0; i<popsz; i++)
            {
                nextgen[i] = NeuralNetwork::recombine(population[bestn], population[secn]);
                population[i]->mutate();
            }

            for (i=0; i<popsz; i++)
            {
                // delete population[i];
                population[i] = nextgen[i];
            }
        }

        // Save the best performing offspring.
        neur = population[bestn];
        fp = fopen(argv[2], "wb");
        if (!fp) return -2;
        neur->write(fp);
        fclose(fp);

        n = eval_outs.size();
        float percent = 0.01 * round((float)mostright / n * 10000);
        cout << endl << "Best result: " << percent << "\% correct." << endl;
    }
    else if (!strcmp(argv[1], "predict"))
    {
        if (argc < 4) return -1;

        FILE* fp = fopen(argv[2], "rb");
        if (!fp) return -2;
        NeuralNetwork* neur = NeuralNetwork::read(fp);
        fclose(fp);

        float input_vals[argc];
        for (i=3; i<argc; i++) input_vals[i-3] = atof(argv[i]);

        int result = neur->predict(input_vals);

        cout << result << " (" << 100*neur->get_confidence() << "%)" << endl;
    }

    return 0;
}