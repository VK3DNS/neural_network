//
// Created by Pepper Scott on 27/8/2025.
//

#pragma once

#ifndef WEIGHT_BIAS_DELTA_H
#define WEIGHT_BIAS_DELTA_H
#include "matrix_functions.h"

void reset_weight_bias_delta(struct BrainHandler *brain) {
    for (int layernum = 0; layernum < brain->num_layers; layernum++) {
        for (int layerneuron = 0; layerneuron < brain->LAYER_COUNT[layernum]; layerneuron++) {
            brain->bias_array[layernum][layerneuron] = 0.0f;
            brain->error_array[layernum][layerneuron] = 0.0f;
        }
    }
}

void update_weight_delta(struct BrainHandler *brain) {

}

void backpropagate(struct BrainHandler *brain) {
}

void gradient(struct BrainHandler *brain, const int expected_output[]) {
    float* nablacost = calloc(brain->outputneurons, sizeof(float));

    for (int i = 0; i < brain->outputneurons; i++) {
        nablacost[i] = cost_derivative(brain, brain->output_array[i], expected_output[i]);
    }

    for (int neuron = 0; neuron < brain->outputneurons; neuron++) {
        //printf("nablacost %d: %f\n", neuron, nablacost[neuron]);
    }

    //iterate first backpropogate also define my current layer matrix for later
    float* current_activation_derivative = brain->activation_derivative_array[brain->num_layers-1];
    brain->error_array[brain->num_layers-1] = hadamard_multiply(current_activation_derivative, nablacost, brain->outputneurons, 1);

    //printf("error: %f\n", brain->error_array[brain->num_layers-1][0]);

    for (int neuron = 0; neuron < brain->LAYER_COUNT[brain->num_layers-2]; neuron++) {
        //printf("sigmoid derivate layer L-2 at neuron %d: %f\n", neuron, brain->activation_derivative_array[brain->num_layers-2][neuron]);
    }

    for (int neuron = 0; neuron < brain->LAYER_COUNT[brain->num_layers-2]; neuron++) {
        //printf("neuron %d: %f\n", neuron, brain->error_array[brain->num_layers-2][neuron]);
    }

    float* weightstransposedraw;

    //printf("numlayers: %d\n", brain->num_layers);

    for (int layer = brain->num_layers-2; layer >= 1; layer--) {
        printf("current layer num: %d\nwidth of last layer: %d, width of current layer: %d\n", layer, brain->LAYER_COUNT[layer-1], brain->LAYER_COUNT[layer]);
        const int row = brain->LAYER_COUNT[layer];
        const int col = brain->LAYER_COUNT[layer+1];

        float** totranspose = brain->weight_array[layer];
        float send[row * col];
        float pretranspose[row][col];

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                send[i * col + j] = totranspose[i][j];
                pretranspose[i][j] = totranspose[i][j];
            }
        }

        printf("(pretranspose) row = %d, col = %d\n", row, col);

        float* out = transpose(send, row, col);

        float (*weightstransposed)[row] = (float (*)[row])out;

        for (int i = 0; i < col; i++) {
            for (int j = 0; j < row; j++) {
                printf("%f\t", weightstransposed[i][j]);
            }
            printf("\n");
        }

        float errorarraycopy[row][1];

        printf("errorarraycopy\n");
        for (int i = 0; i < col; i++) {
            errorarraycopy[i][0] = brain->error_array[layer+1][i];
            printf("%f\t", brain->error_array[layer+1][i]);
        }
        printf("\n\n");

        float (*multiplicationproduct)[col] = matrix_multiply(pretranspose, errorarraycopy, brain->LAYER_COUNT[layer], brain->LAYER_COUNT[layer+1], 1);

        printf("multiplicationproduct\n");
        for (int j = 0; j < row; j++) {
            for (int i = 0; i < col; i++) {
                printf("%f\t", multiplicationproduct[i][j]);
            }
            printf("\n");
        }

        float* current_activation_derivative = brain->activation_derivative_array[brain->num_layers-1];

        brain->error_array[layer] = hadamard_multiply(multiplicationproduct, brain->activation_derivative_array[layer], col, row);

        printf("hadamard_multiply\n");
        for (int i = 0; i < row; i++) {
            printf("%f\t", brain->error_array[layer][i]);
        }

        for (int neuron = 0; neuron < brain->LAYER_COUNT[layer-1]; neuron++) {
            //printf("layer %d error at neuron %d: %f\n", i-1, neuron, brain->error_array[i-1][neuron]);
        }
        //printf("\n");
    }

    free(nablacost);
}

#endif
