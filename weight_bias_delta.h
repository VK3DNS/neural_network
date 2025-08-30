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

void gradient(struct BrainHandler *brain, const float* expected_output) {

    float* nablacost = calloc(brain->outputneurons, sizeof(float));
    for (int i = 0; i < brain->outputneurons; i++) {
        nablacost[i] = cost_derivative(brain, brain->output_array[i], expected_output[i]);
    }

    float* current_activation_derivative = brain->activation_derivative_array[brain->num_layers-1];
    brain->error_array[brain->num_layers-1] =
        hadamard_multiply(current_activation_derivative, nablacost, brain->outputneurons, 1);

    for (int layer = brain->num_layers - 2; layer >= 0; layer--) {
        const int row = brain->LAYER_COUNT[layer];
        const int col = brain->LAYER_COUNT[layer + 1];

        float send[row * col];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                send[i * col + j] = brain->weight_array[layer][i][j];
            }
        }

        /*
        printf("Activation derivatives at layer %d:\n", layer);
        for (int i = 0; i < brain->LAYER_COUNT[layer]; i++) {
            printf("%f ", brain->activation_derivative_array[layer][i]);
        }
        printf("\n");
        */

        float* wT = transpose(send, row, col);

        float* multiplicationproduct = matrix_multiply(wT, brain->error_array[layer+1], col, row, 1);

        brain->error_array[layer] =
            hadamard_multiply(multiplicationproduct, brain->activation_derivative_array[layer], row, 1);

        free(wT);
        free(multiplicationproduct);
    }

    free(nablacost);
}

void change_weights_and_biases(struct BrainHandler *brain) {
    for (int layer = 0; layer < brain->num_layers - 1; layer++) {
        const int row = brain->LAYER_COUNT[layer];
        const int col = brain->LAYER_COUNT[layer + 1];

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                float delta_weight = -brain->learningrate * brain->node_array[layer][i] * brain->error_array[layer+1][j];
                brain->weight_array[layer][i][j] += delta_weight;
            }
        }

        for (int j = 0; j < col; j++) {
            float delta_bias = -brain->learningrate * brain->error_array[layer+1][j];
            brain->bias_array[layer+1][j] += delta_bias;
        }
    }
}

#endif
