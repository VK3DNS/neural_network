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

    int hidden_layer_neurons[] = {10,4,4};
    int num_hidden_layers = sizeof(hidden_layer_neurons)/sizeof(hidden_layer_neurons[0]);

    struct BrainHandler *brain = init(inputneurons, hidden_layer_neurons, outputneurons, num_hidden_layers, 0);
    const float inputs[] = {0.0f, 0.0f};

    setfirstlayer(inputs, brain);
    updatebrain(brain);

    //print_weight(brain);
    print_node(brain);


    const int row = 2;
    const int col = 3;

    int matrix[row][col] = {
        {1,2,3},
        {4,5,6}
    };

    int elemsize = sizeof(int);

    void* out = transpose(matrix, row, col, elemsize);

    int (*matrix2d)[row] = (int (*)[row])out;

    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            printf("%d ", matrix2d[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    void* out2 = scalar_multiply_int(matrix2d, col, row, 2);
    void* out3 = scalar_multiply_float(matrix2d, col, row, 2);
    int (*matrix2d2)[row] = (int (*)[row])out2;
    float (*matrix2d3)[row] = (float (*)[row])out3;

    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            printf("%d ", matrix2d2[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            printf("%f ", matrix2d3[i][j]);
        }
        printf("\n");
    }



    /*
    for (int i = 0; i < outputneurons; i++) {
        printf("Output Neuron %d: %f\n", i, brain->output_array[i]);
    }
    */

    calculate_cost(brain, testout[0], outputneurons);

    free_brain(brain);
    return 0;
}