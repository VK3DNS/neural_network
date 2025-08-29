//
// Created by Pepper Scott on 26/8/2025.
//

#ifndef defaults
#define defaults
const float default_weight = 0.5f;
const int inputneurons = 2;
const int outputneurons = 1;
const int numtestcases = 4;
#endif

#ifndef testcases
#define testcases
float testin[numtestcases][inputneurons] = {
    {1,1},
    {1,3},
    {1,4},
    {0,5}
};
float testout[numtestcases][outputneurons] = {
    {0},
    {1},
    {0},
    {0}
};
#endif

#include "imports.h"

int main(void) {
    int hidden_layer_neurons[] = {3,2,3};
    int numhiddenlayers = sizeof(hidden_layer_neurons)/sizeof(hidden_layer_neurons[0]);

    struct BrainHandler *brain = init(inputneurons, hidden_layer_neurons, outputneurons, numhiddenlayers, 0);

    for (int testcase = 0; testcase <=0; testcase++) {
        printf("Testcase %d:\n", testcase);
        const int inputlength = sizeof(testin[testcase])/sizeof(testin[testcase][0]);
        process(brain, testin[testcase], inputlength, testout[testcase]);
        printf("\n\n\n");
    }

    free_brain(brain);
    return 0;
}