//
// Created by Pepper Scott on 27/8/2025.
//

#pragma once

#ifndef COST_H
#define COST_H
#include <math.h>

void calculate_cost(struct BrainHandler *brain, const int expected_output[], const int output_neurons) {
    float cost = 0.0f;
    for (int i = 0; i < output_neurons; i++) {
        float error = brain->output_array[i] - expected_output[i];
        cost += pow(error, 2);
    }
    cost /= output_neurons;
    printf("Cost: %f\n", cost);
}

#endif
