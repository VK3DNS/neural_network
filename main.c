//
// Created by Pepper Scott on 26/8/2025.
//

#ifndef defaults
#define defaults
const int inputneurons = 2;
const int outputneurons = 2;
const int numtestcases = 4;
const float learningrate = 1.0f;
int trainingcycles = 10000000;
#endif

#ifndef testcases
#define testcases
float testin[numtestcases][inputneurons] = {
    {0,0},
    {0,1},
    {1,0},
    {1,1}
};
float testout[numtestcases][outputneurons] = {
    {1,0},
    {0,1},
    {0,1},
    {1,0}
};
#endif

#include "imports.h"

float (*default_weight) = randnum;

[[noreturn]] int main(void) {
    int hidden_layer_neurons[] = {3,3};
    int numhiddenlayers = sizeof(hidden_layer_neurons)/sizeof(hidden_layer_neurons[0]);

    struct BrainHandler *brain = init(inputneurons, hidden_layer_neurons, outputneurons, numhiddenlayers, learningrate, default_weight);

    for (int testcase = 0; testcase < trainingcycles; testcase++) {
        int testnum = testcase % numtestcases ;
        const int inputlength = sizeof(testin[testnum])/sizeof(testin[testnum][0]);
        process(brain, testin[testnum], inputlength, testout[testnum]);
    }

    /*
    print_weight(brain);
    printf("\n\n");
    print_bias(brain);
    */

    while (1) {
        float inputs[inputneurons] = {0,0};

        for (int i = 0; i < inputneurons; i++) {
            printf("Input %d: ", i);
            scanf("%f", &inputs[i]);
        }
        process(brain, inputs, inputneurons, NULL);
    }

    free_brain(brain);
    return 0;
}