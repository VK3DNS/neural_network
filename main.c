//
// Created by Pepper Scott on 26/8/2025.
//

//#define testcases

#ifndef defaults
#define defaults

#ifdef testcases
const int inputneurons = 2;
const int outputneurons = 2;
const int numtestcases = 4;
const double learningrate = 1;

#else
const int inputneurons = 64;
const int outputneurons = 10;
const int numtestcases = 200;
#endif


int trainingcycles = 10000000;

#endif

#ifdef testcases
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
#endif

#include "imports.h"

double (*default_weight)() = randnum;
double (*learningrate_func)(struct BrainHandler*) = learning_rate;

[[noreturn]] int main(void) {
    int hidden_layer_neurons[] = {16,16};
    int numhiddenlayers = sizeof(hidden_layer_neurons)/sizeof(hidden_layer_neurons[0]);

    struct BrainHandler *brain = init(inputneurons, hidden_layer_neurons, outputneurons, numhiddenlayers, default_weight, trainingcycles, learningrate_func);

    for (int testcase = 0; testcase < trainingcycles; testcase++) {
        if (testcase % 1000000 == 0) {
            printf("Training cycle: %d / %d\n", testcase, trainingcycles);
        }
        int testnum = testcase % numtestcases ;
        const int inputlength = sizeof(testin[testnum])/sizeof(testin[testnum][0]);
        process(brain, testin[testnum], inputlength, testout[testnum], testcase);
    }


    print_weight(brain);
    printf("\n\n");
    print_bias(brain);
    //printf("\n\n");
    //print_error(brain);


    while (1) {
        double* inputs = malloc(inputneurons*sizeof(double));

        inputs = read_binary_input(&inputneurons);

        process(brain, inputs, inputneurons, NULL, -1);
    }

    free_brain(brain);
    //return 0;
}