//
// Created by Pepper Scott on 26/8/2025.
//

#pragma once

#ifndef stdio_h
#define stdio_h
#include <stdio.h>
#endif

#ifndef stdlib_h
#define stdlib_h
#include <stdlib.h>
#endif

#ifndef math_h
#define math_h
#include <math.h>
#endif

#ifndef defaults
#define defaults
const int LAYER_COUNT[] = {2,10,4,4,1};
const double default_weight = 0.5f;
#endif

#ifndef INITNETWORK_H
#define INITNETWORK_H

struct BrainHandler{
    int testq;
    int testnum;

    int* LAYER_COUNT;
    double (*default_weight)();

    int num_layers;
    double*** weight_array;
    double** node_array;

    double** z_array;
    double** bias_array;
    double** error_array;
    double** activation_derivative_array;

    double* output_array;

    int inputneurons;
    int outputneurons;

    double (*learningrate_func)(struct BrainHandler*);

    int epoch;
    int total_epochs;
};

double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double sigmoid_derivative(double x) {
    return exp(-x)/pow(1 + exp(-x), 2);
}

double randnum() {
    return (double)rand() / (double)RAND_MAX;
}

struct BrainHandler* init(int inputneurons, const int hidden_layer_neurons[], const int outputneurons, const int numhiddenlayers, double (*default_weight)(), int trainingcycles, double (*learningrate_func)(struct BrainHandler*)) {
    struct BrainHandler* brain = (struct BrainHandler*)malloc(sizeof(struct BrainHandler));

    brain->epoch = 0;
    brain->total_epochs = trainingcycles;
    brain->learningrate_func = learningrate_func;

    int* layer_neuron_nums = malloc((2 + numhiddenlayers) * sizeof(int));

    layer_neuron_nums[0] = inputneurons;
    for (int i = 0; i < numhiddenlayers; i++) {
        layer_neuron_nums[1 + i] = hidden_layer_neurons[i];
    }
    layer_neuron_nums[1 + numhiddenlayers] = outputneurons;

    int num_layers = 2 + numhiddenlayers;

    if (brain == NULL) {
        fprintf(stderr, "Memory allocation failed for brain\n");
        exit(EXIT_FAILURE);
    }

    brain->LAYER_COUNT = (int*)malloc(num_layers * sizeof(int));
    brain->default_weight = default_weight;
    brain->num_layers = num_layers;
    brain->weight_array = (double***)malloc(brain->num_layers * sizeof(double**));
    brain->node_array = (double**)malloc(brain->num_layers * sizeof(double*));

    brain->z_array = (double**)malloc(brain->num_layers * sizeof(double*));
    brain->bias_array = (double**)malloc(brain->num_layers * sizeof(double*));
    brain->error_array = (double**)malloc(brain->num_layers * sizeof(double*));
    brain->activation_derivative_array = (double**)malloc(brain->num_layers * sizeof(double*));

    brain->output_array = (double*)malloc(outputneurons * sizeof(double));

    brain->inputneurons = inputneurons;
    brain->outputneurons = outputneurons;

    for (int i = 0; i < num_layers; i++) {
        brain->LAYER_COUNT[i] = layer_neuron_nums[i];
    }

    for (int layernum = 0; layernum < brain->num_layers; layernum++) {
        brain->weight_array[layernum] = (double**)malloc(layer_neuron_nums[layernum] * sizeof(double*));

        brain->node_array[layernum] = (double*)malloc(layer_neuron_nums[layernum] * sizeof(double));

        brain->z_array[layernum] = (double*)malloc(layer_neuron_nums[layernum] * sizeof(double));
        brain->bias_array[layernum] = (double*)malloc(layer_neuron_nums[layernum] * sizeof(double));
        brain->error_array[layernum] = (double*)malloc(layer_neuron_nums[layernum] * sizeof(double));
        brain->activation_derivative_array[layernum] = (double*)malloc(layer_neuron_nums[layernum] * sizeof(double));

        for (int j = 0; j < layer_neuron_nums[layernum]; j++) {
            brain->bias_array[layernum][j] = 0.0f;
            brain->error_array[layernum][j] = 0.0f;
        }

        for (int layerneuron = 0; layerneuron < layer_neuron_nums[layernum]; layerneuron++) {
            if (layernum < brain->num_layers - 1) {
                brain->weight_array[layernum][layerneuron] = (double*)malloc(layer_neuron_nums[layernum+1] * sizeof(double));

                for (int nextlayerweight = 0; nextlayerweight < layer_neuron_nums[layernum+1]; nextlayerweight++) {
                    brain->weight_array[layernum][layerneuron][nextlayerweight] = default_weight();
                }
            } else {
                brain->weight_array[layernum][layerneuron] = NULL;
            }
            brain->node_array[layernum][layerneuron] = 0.0f;
        }
    }

    free(layer_neuron_nums);
    return brain;
}

void free_brain(struct BrainHandler* brain) {

    if (brain) {
        for (int l = 0; l < brain->num_layers; l++) {
            for (int n = 0; n < brain->LAYER_COUNT[l]; n++) {
                if (brain->weight_array[l][n] != NULL) {
                    free(brain->weight_array[l][n]);
                }
            }
            free(brain->weight_array[l]);
            free(brain->node_array[l]);

            free(brain->z_array[l]);
            free(brain->bias_array[l]);
            free(brain->error_array[l]);
        }

        free(brain->output_array);
        free(brain->LAYER_COUNT);

        free(brain->weight_array);
        free(brain->node_array);
        free(brain);
    }
}

#endif INITNETWORK_H
