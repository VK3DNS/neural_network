//
// Created by Pepper Scott on 27/8/2025.
//

#pragma once

#ifndef COST_H
#define COST_H
#include <math.h>

float calculate_cost(struct BrainHandler *brain, const int expected_output[]) {
    float cost = 0.0f;
    for (int i = 0; i < brain->outputneurons; i++) {
        float error = brain->output_array[i] - expected_output[i];
        cost += pow(error, 2);
    }
    cost /= 2;
    printf("Cost: %f\n", cost);
    return cost;
}

float cost_derivative(struct BrainHandler* brain, float output, int expected) {
    return (output - expected);
}

#endif
