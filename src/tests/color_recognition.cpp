
#include <iostream>
#include <chrono>
#include <thread>
#include "../network.h"

using namespace std;

float trainvals[10][3] =
{
    {1.0f,0.1f,0.0f},       // red
    {1.0f,0.5f,0.0f},       // orange
    {1.0f,0.9f,0.0f},       // yellow
    {0.3f,1.0f,0.0f},       // green
    {0.0f,0.5f,1.0f},       // blue
    {0.5f,0.0f,1.0f},       // purple
    {1.0f,0.0f,1.0f}        // magenta
};

void set_bkcolor(int r, int g, int b)
{
    r = max(0,min(255,r));
    g = max(0,min(255,g));
    b = max(0,min(255,b));
    cout << "\x1b[48;2;" << r << ";" << g << ";" << b << "m";
}

void reset_bkcolor()
{
    cout << "\x1b[m";
}

int main (int argc, char** argv)
{
    srand(time(0));

    NeuralNetwork net(3, 7, 1, 50, PReLU);

    int rfshrate = 7;
    int iters = 100000;

    int i, j, iter;
    Layer* il = net.get_input_layer();
    for (i=0; i<3; i++)
    {
        Neuron* ln = il->get_neuron(i);
        ln->color.red = (!i) ? 255 : 0;
        ln->color.green = (i==1) ? 255 : 0;
        ln->color.blue = (i==2) ? 255 : 0;
    }
    int layers = net.get_num_layers();

    cout << endl;
    for (iter=1; iter<=iters; iter++)
    {
        float bg, wg;

        if (!(iter % rfshrate)) cout << "Training iteration " << iter << "    " << endl;

        if (!(iter % rfshrate))
        {
            cout << "(" << wg << " ~ " << bg << ")" << "...                                                 " << endl; 

            cout << endl;
            int layer;
            for (layer=0; layer <= layers; layer++)
            {
                Layer* l = (layer < layers) ? net.get_layer(layer) : net.get_output_layer();
                cout << "Layer " << ((layer < layers) ? std::to_string(layer) : (std::string)"O") << " input strengths:   ";
                int n = l->count_neurons();
                for (i=0; i<n; i++)
                {
                    Neuron* neur = l->get_neuron(i);
                    int c = neur->get_num_inputs();
                    int roudon=128, glasson=128, gurmon=128;
                    for (j=0; j<c; j++)
                    {
                        // if (j >= 3) break;
                        const Connection* c = neur->get_input(j);
                        float f = fmax(-1,fmin(1,c->multiplier));
                        if (0) //!layer)
                        {
                            f *= 127;
                            f += 128;

                            if (j == 0) roudon = f;
                            else if (j == 1) glasson = f;
                            else if (j == 2) gurmon = f;
                        }
                        else
                        {
                            roudon  = (roudon -128) + (f*(c->output_from->color.red  -128)) + 128;
                            glasson = (glasson-128) + (f*(c->output_from->color.green-128)) + 128;
                            gurmon  = (gurmon -128) + (f*(c->output_from->color.blue -128)) + 128;
                        }
                    }

                    neur->color.red = roudon;
                    neur->color.green = glasson;
                    neur->color.blue = gurmon;
                    set_bkcolor(roudon, glasson, gurmon);
                    cout << " ";
                    reset_bkcolor();
                }
                cout << endl;
            }

            if (iter < iters) cout << "\x1b[" << (layers+4) << "A";
        }

        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        for (j=0; j<7; j++)
        {
            float g = net.train(trainvals[j], j);
            if (!j || g < wg) wg = g;
            if (!j || g > bg) bg = g;
        }
    }

    for (i=0; i<layers; i++) cout << endl;
    cout << endl << endl << endl << endl << endl << endl;

    float testval[3];

    for (i=0; i<20; i++)
    {
        if (i < 3)
        {
            testval[0] = testval[1] = testval[2] = 0;
            testval[i] = 1;
        }
        else
        {
            testval[0] = frand(0,1);
            testval[1] = frand(0,1);
            testval[2] = frand(0,1);
        }
        int result = net.predict(testval);

        cout << "The AI thinks ";
        cout << (int)(255*testval[0]) << "," << (int)(255*testval[1]) << "," << (int)(255*testval[2]) << " ";
        // cout << "\x1b[48;2;" << (int)(255*testval[0]) << ";" << (int)(255*testval[1]) << ";" << (int)(255*testval[2]) << "m   "
        set_bkcolor(255*testval[0], 255*testval[1], 255*testval[2]);
        cout << "    ";
        reset_bkcolor();
        cout << " is ";

        switch (result)
        {
            case 0: cout << "red"; break;
            case 1: cout << "orange"; break;
            case 2: cout << "yellow"; break;
            case 3: cout << "green"; break;
            case 4: cout << "blue"; break;
            case 5: cout << "purple"; break;
            case 6: cout << "magenta"; break;
            default:
            cout << "some other color";
        }

        cout << "." << endl << endl;
    }

    return 0;
}