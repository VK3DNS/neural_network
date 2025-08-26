//
// Created by Nathan Scott on 26/8/2025.
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

#ifndef PRINTER_H
#define PRINTER_H

void print_weight(struct BrainHandler *brain) {
    printf("Weight Structure:\n");
    for (int layernum = 0; layernum < brain->num_layers; layernum++) {
        for (int layerneuron = 0; layerneuron < brain->LAYER_COUNT[layernum]; layerneuron++) {
            printf("Layer %d Neuron %d: ", layernum, layerneuron);
            if (layernum < brain->num_layers - 1 && brain->weight_array[layernum][layerneuron] != NULL) {
                for (int nextlayerweight = 0; nextlayerweight < brain->LAYER_COUNT[layernum+1]; nextlayerweight++) {
                    printf("%f ", brain->weight_array[layernum][layerneuron][nextlayerweight]);
                }
            } else {
                printf("No outgoing weights (output layer)");
            }
            printf("\n");
        }
    }
}

void print_node(struct BrainHandler *brain) {
    for (int layernum = 0; layernum < brain->num_layers; layernum++) {
        for (int layerneuron = 0; layerneuron < brain->LAYER_COUNT[layernum]; layerneuron++) {
            printf("Layer %d Neuron %d: %f\n", layernum, layerneuron, brain->node_array[layernum][layerneuron]);
        }
    }
}

#endif
