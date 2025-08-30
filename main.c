//
// Created by Pepper Scott on 26/8/2025.
//

#define testcases

#ifndef defaults
#define defaults
//const int inputneurons = 64;
//const int outputneurons = 10;
//const int numtestcases = 100;
const int inputneurons = 2;
const int outputneurons = 2;
const int numtestcases = 4;
const double learningrate = 1;
int trainingcycles = 10000000;
#endif

#include "imports.h"

double testin[numtestcases][inputneurons] = {
{0.0,0.0},
{0.0,1.0},
{1.0,0.0},
{1.0,1.0}
};

double testout[numtestcases][outputneurons] = {
{1.0,0.0},
{0.0,1.0},
{0.0,1.0},
{1.0,0.0}
};

double (*default_weight) = randnum;

[[noreturn]] int main(void) {
    int hidden_layer_neurons[] = {10,10};
    int numhiddenlayers = sizeof(hidden_layer_neurons)/sizeof(hidden_layer_neurons[0]);

    struct BrainHandler *brain = init(inputneurons, hidden_layer_neurons, outputneurons, numhiddenlayers, learningrate, default_weight);

    for (int testcase = 0; testcase < trainingcycles; testcase++) {
        int testnum = testcase % numtestcases ;
        const int inputlength = sizeof(testin[testnum])/sizeof(testin[testnum][0]);
        process(brain, testin[testnum], inputlength, testout[testnum]);
    }


    print_weight(brain);
    printf("\n\n");
    print_bias(brain);
    printf("\n\n");
    print_error(brain);


    while (1) {
        double* inputs = malloc(inputneurons*sizeof(double));

        inputs = read_binary_input(&inputneurons);

        for (int i = 0; i < inputneurons; i++) {
            printf("%lf ", inputs[i]);
        }
        printf("\n");
        process(brain, inputs, inputneurons, NULL);
    }

    free_brain(brain);
    return 0;
}