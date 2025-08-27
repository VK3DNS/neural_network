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
const float default_weight = 0.5f;
#endif

#ifndef INITNETWORK_H
#define INITNETWORK_H

struct BrainHandler{
    int testq;
    int testnum;

    int* LAYER_COUNT;
    float default_weight;

    int num_layers;
    float*** weight_array;
    float** node_array;
};

float sigmoid(float x) {
    return 1 / (1 + exp(-x));
}

struct BrainHandler* init(int inputneurons, const int hidden_layer_neurons[], const int outputneurons, const int numhiddenlayers, int testq) {
    struct BrainHandler* brain = (struct BrainHandler*)malloc(sizeof(struct BrainHandler));

    int* layer_neuron_nums = malloc((2 + numhiddenlayers) * sizeof(int));
    if (layer_neuron_nums == NULL) {
        fprintf(stderr, "Memory allocation failed for layer_neuron_nums\n");
        free(brain);
        exit(EXIT_FAILURE);
    }

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

    brain->LAYER_COUNT = layer_neuron_nums;
    brain->default_weight = default_weight;
    brain->num_layers = num_layers;
    brain->weight_array = (float***)malloc(brain->num_layers * sizeof(float**));
    brain->node_array = (float**)malloc(brain->num_layers * sizeof(float*));

    brain->weight_array = (float***)malloc(brain->num_layers * sizeof(float**));
    if (brain->weight_array == NULL) {
        fprintf(stderr, "Memory allocation failed for weight_array\n");
        free(brain);
        exit(EXIT_FAILURE);
    }
    brain->node_array = (float**)malloc(brain->num_layers * sizeof(float*));
    if (brain->node_array == NULL) {
        fprintf(stderr, "Memory allocation failed for node_array\n");
        free(brain->weight_array);
        free(brain);
        exit(EXIT_FAILURE);
    }

    for (int layernum = 0; layernum < brain->num_layers; layernum++) {
        brain->weight_array[layernum] = (float**)malloc(layer_neuron_nums[layernum] * sizeof(float*));
        if (brain->weight_array[layernum] == NULL) {
            fprintf(stderr, "Memory allocation failed for weight_array[%d]\n", layernum);
            exit(EXIT_FAILURE);
        }
        brain->node_array[layernum] = (float*)malloc(layer_neuron_nums[layernum] * sizeof(float));
        if (brain->node_array[layernum] == NULL) {
            fprintf(stderr, "Memory allocation failed for node_array[%d]\n", layernum);
            exit(EXIT_FAILURE);
        }
        for (int layerneuron = 0; layerneuron < layer_neuron_nums[layernum]; layerneuron++) {
            if (layernum < brain->num_layers - 1) {
                brain->weight_array[layernum][layerneuron] = (float*)malloc(layer_neuron_nums[layernum+1] * sizeof(float));
                if (brain->weight_array[layernum][layerneuron] == NULL) {
                    fprintf(stderr, "Memory allocation failed for weight_array[%d][%d]\n", layernum, layerneuron);
                    exit(EXIT_FAILURE);
                }
                for (int nextlayerweight = 0; nextlayerweight < layer_neuron_nums[layernum+1]; nextlayerweight++) {
                    brain->weight_array[layernum][layerneuron][nextlayerweight] = default_weight;
                }
            } else {
                brain->weight_array[layernum][layerneuron] = NULL;
            }
            brain->node_array[layernum][layerneuron] = 0.0f;
        }
    }

    //print_weight();
    //printf("\n\n");
    //print_node();
    return brain;
}

void free_brain(struct BrainHandler* brain) {
    for (int l = 0; l < brain->num_layers; l++) {
        for (int n = 0; n < brain->LAYER_COUNT[l]; n++) {
            if (brain->weight_array[l][n] != NULL) {
                free(brain->weight_array[l][n]);
            }
        }
        free(brain->weight_array[l]);
        free(brain->node_array[l]);
    }
    free(brain->weight_array);
    free(brain->node_array);
    free(brain);
}

#endif INITNETWORK_H
