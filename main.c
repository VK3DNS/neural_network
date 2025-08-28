//
// Created by Pepper Scott on 26/8/2025.
//

#ifndef defaults
#define defaults
const float default_weight = 0.5f;
const int inputneurons = 2;
const int outputneurons = 1;
const int numtestcases = 2;
#endif

#ifndef testcases
#define testcases
int testin[numtestcases][inputneurons] = {
    {0,0},
    {1,1}
};
int testout[numtestcases][outputneurons] = {
    {0},
    {1}
};
#endif

#include "imports.h"

int main(void) {
    int testing = 1;

    int hidden_layer_neurons[] = {3};
    int num_hidden_layers = sizeof(hidden_layer_neurons)/sizeof(hidden_layer_neurons[0]);


    struct BrainHandler *brain = init(inputneurons, hidden_layer_neurons, outputneurons, num_hidden_layers, 0);
    const float inputs[] = {1.0f, 1.0f};


    setfirstlayer(inputs, brain);
    updatebrain(brain);

    float current_activation_derivative[3][2] = {
        {0.25f, 0.35f},
        {0.45f, 0.55f},
        {0.65f, 0.75f}
    };

    float nablacost[2][1] = {
        {0.3f},
        {0.9f}
    };

    const int row = 3;
    const int col = 1;

    float* out = matrix_multiply_float(current_activation_derivative, nablacost, 3, 2, 1);

    float (*matrix2d3)[row] = (float (*)[row])out;

    for (int i = 0; i < 3; i++) {
        printf("%f\n", out[i]);
    }

    //print_weight(brain);
    print_node(brain);

    calculate_cost(brain, testout[0]);

    printf("\n\n");

    gradient(brain, testout[0]);

    free_brain(brain);
    return 0;
}