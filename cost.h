//
// Created by Pepper Scott on 27/8/2025.
//

#pragma once

#ifndef COST_H
#define COST_H
#include <math.h>

double calculate_cost(struct BrainHandler *brain, const double expected_output[]) {
    double cost = 0.0;
    for (int i = 0; i < brain->outputneurons; i++) {
        double error = brain->output_array[i] - expected_output[i];
        cost += pow(error, 2);
    }
    cost /= 2;
    printf("Cost: %f\n", cost);
    return cost;
}

double cost_derivative(struct BrainHandler* brain, double output, int expected) {
    return (output - expected);
}

#endif
