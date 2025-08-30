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
const float learningrate = 0.01f;
int trainingcycles = 100000;
#endif

#include "imports.h"

float testin[numtestcases][inputneurons] = {
{0.0f,0.0f},
{0.0f,1.0f},
{1.0f,0.0f},
{1.0f,1.0f}
};

float testout[numtestcases][outputneurons] = {
{1.0f,0.0f},
{0.0f,1.0f},
{0.0f,1.0f},
{1.0f,0.0f}
};

float (*default_weight) = randnum;

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
        float* inputs = malloc(inputneurons*sizeof(float));

        inputs = read_binary_input(&inputneurons);

        for (int i = 0; i < inputneurons; i++) {
            printf("%f ", inputs[i]);
        }
        printf("\n");
        process(brain, inputs, inputneurons, NULL);
    }

    free_brain(brain);
    return 0;
}