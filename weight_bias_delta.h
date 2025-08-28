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
        printf("nablacost %d: %f\n", neuron, nablacost[neuron]);
    }

    //iterate first backpropogate also define my current layer matrix for later
    float* current_activation_derivative = brain->activation_derivative_array[brain->num_layers-1];
    brain->error_array[brain->num_layers-1] = hadamard_multiply_float(current_activation_derivative, nablacost, brain->outputneurons, 1);

    printf("error: %f\n", brain->error_array[brain->num_layers-1][0]);

    for (int neuron = 0; neuron < brain->LAYER_COUNT[brain->num_layers-2]; neuron++) {
        printf("sigmoid derivate layer L-2 at neuron %d: %f\n", neuron, brain->activation_derivative_array[brain->num_layers-2][neuron]);
    }

    for (int neuron = 0; neuron < brain->LAYER_COUNT[brain->num_layers-2]; neuron++) {
        printf("neuron %d: %f\n", neuron, brain->error_array[brain->num_layers-2][neuron]);
    }

    float* weightstransposedraw;
    float* multiplicationproduct;

    printf("numlayers: %d\n", brain->num_layers);

    for (int i = brain->num_layers-2; i >= 1; i--) {
        printf("current layer num: %d\nwidth of last layer: %d, width of current layer: %d\n", i, brain->LAYER_COUNT[i-1], brain->LAYER_COUNT[i]);
        weightstransposedraw = transpose(brain->weight_array[i], brain->LAYER_COUNT[i], brain->LAYER_COUNT[i-1], sizeof(float));

        float (*weightstransposed)[brain->LAYER_COUNT[i-1]] = (float (*)[brain->LAYER_COUNT[i-1]])weightstransposedraw;

        for (int j = 0; j < brain->LAYER_COUNT[i-1]; j++) {
            for (int k = 0; k < brain->LAYER_COUNT[i]; k++) {
                printf("weightstransposed %d,%d: %f\n", j, k, weightstransposed[j][k]);
            }
        }

        multiplicationproduct = matrix_multiply_float(weightstransposed, brain->error_array[i], brain->LAYER_COUNT[i-1], brain->LAYER_COUNT[i], 1);
        brain->error_array[i-1] = hadamard_multiply_float(brain->activation_derivative_array[i-1], multiplicationproduct, brain->LAYER_COUNT[i-1], 1);

        for (int neuron = 0; neuron < brain->LAYER_COUNT[i-1]; neuron++) {
            printf("layer %d error at neuron %d: %f\n", i-1, neuron, brain->error_array[i-1][neuron]);
        }
        //printf("\n");
    }

    free(nablacost);
}

#endif
