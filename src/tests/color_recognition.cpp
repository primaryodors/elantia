
#include <iostream>
#include "../network.h"

using namespace std;

float trainvals[10][3] =
{
    {0.0f,0.0f,0.0f},       // black
    {0.5f,0.5f,0.5f},       // gray
    {1.0f,1.0f,1.0f},       // white
    {0.5f,0.3f,0.1f},       // brown
    {1.0f,0.0f,0.0f},       // red
    {1.0f,0.5f,0.0f},       // orange
    {1.0f,1.0f,0.0f},       // yellow
    {0.0f,1.0f,0.0f},       // green
    {0.0f,0.5f,1.0f},       // blue
    {0.7f,0.0f,0.1f}        // purple
};

int main (int argc, char** argv)
{
    srand(time(0));

    NeuralNetwork net(3, 10, 3, 20, Sigmoid);

    int i, j;
    for (i=0; i<200; i++)
    {
        float bg, wg;
        if (!(i % 53)) cout << "Training iteration " << i << endl;
        for (j=0; j<10; j++)
        {
            float g = net.train(trainvals[j], j);
            if (!j || g < wg) wg = g;
            if (!j || g > bg) bg = g;
        }
        if (!(i % 53)) cout << "(" << wg << " ~ " << bg << ")" << "...                                                 " << endl << "\x1b[A\x1b[A";
    }

    float testval[3];

    for (i=0; i<10; i++)
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

        cout << "The AI thinks "
             << (int)(255*testval[0]) << "," << (int)(255*testval[1]) << "," << (int)(255*testval[2]) << " "
             << "\x1b[48;2;" << (int)(255*testval[0]) << ";" << (int)(255*testval[1]) << ";" << (int)(255*testval[2]) << "m   "
             << "\x1b[m is ";

        switch (result)
        {
            case 0: cout << "black"; break;
            case 1: cout << "gray"; break;
            case 2: cout << "white"; break;
            case 3: cout << "brown"; break;
            case 4: cout << "red"; break;
            case 5: cout << "orange"; break;
            case 6: cout << "yellow"; break;
            case 7: cout << "green"; break;
            case 8: cout << "blue"; break;
            case 9: cout << "purple"; break;
            default:
            cout << "some other color";
        }

        cout << "." << endl;
    }

    return 0;
}