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


    const int row = 2;
    const int col = 3;

    float** totranspose = brain->weight_array[0];

    float send[row * col];

    /*
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            send[i * col + j] = totranspose[i][j];
            printf("%f", totranspose[i][j]);
        }
        printf("\n");
    }
    */

    //printf("row = %d, col = %d\n", brain->LAYER_COUNT[0], brain->LAYER_COUNT[1]);

    //float* out = transpose(send, brain->LAYER_COUNT[0], brain->LAYER_COUNT[1]);

    //float (*matrix2d)[row] = (float (*)[row])out;

    /*
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            printf("%f\t", matrix2d[i][j]);
        }
        printf("\n");
    }
    */


    //print_weight(brain);
    //print_node(brain);

    //calculate_cost(brain, testout[0]);

    //printf("\n\n");

    /*
    float multiply1[3][2] = {
        {0.5f, 0.6f},
        {0.7f, 0.8f},
        {0.9f, 1.0f}
    };

    float multiply2[2][1] = {
        {0.3f},
        {0.9f}
    };

    float (*mutiplyout)[col] = matrix_multiply(multiply1, multiply2, 3, 2, 1);

    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f\t", mutiplyout[i][j]);
        }
        printf("\n");
    }
    */

    gradient(brain, testout[0]);

    free_brain(brain);
    return 0;
}