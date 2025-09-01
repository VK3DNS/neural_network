//
// Created by Pepper Scott on 26/8/2025.
//

//todo: remind Tsudae to make a GitHub account so I can add them as a parent of this silly little eeb

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

/////////////////////10000000 ten million
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

double (*defaultweight_func)() = randnum;
double (*learningrate_func)(struct BrainHandler*) = learning_rate;

double (*activation_func)(double x) = activation;
double (*activation_derivative_func)(double x) = activationderivative;

[[noreturn]] int main(void) {
    int hidden_layer_neurons[] = {16,16};
    int numhiddenlayers = sizeof(hidden_layer_neurons)/sizeof(hidden_layer_neurons[0]);

    struct BrainHandler *brain = init(inputneurons, hidden_layer_neurons, outputneurons, numhiddenlayers, defaultweight_func, trainingcycles, learningrate_func, activation_func, activation_derivative_func);

    printf("Training cycle: %d / %d\n", 0, trainingcycles);
    for (int testcase = 0; testcase < trainingcycles; testcase++) {
        if ((testcase+1) % 1000000 == 0) {
            printf("Training cycle: %d / %d\n", testcase+1, trainingcycles);
        }
        int testnum = testcase % numtestcases ;
        const int inputlength = sizeof(testin[testnum])/sizeof(testin[testnum][0]);
        process(brain, testin[testnum], inputlength, testout[testnum], testcase);
    }

    printf("\n\n");
    print_weight(brain);
    printf("\n\n");
    print_bias(brain);
    printf("\n\n");
    //print_error(brain);


    while (1) {
        double* inputs = malloc(inputneurons*sizeof(double));

        inputs = read_binary_input(&inputneurons);

        process(brain, inputs, inputneurons, NULL, -1);
    }

    free_brain(brain);
    //return 0;
}