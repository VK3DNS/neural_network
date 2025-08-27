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

#ifndef UPDATE_H
#define UPDATE_H

void setfirstlayer(const float* inputs, const struct BrainHandler *brain) {
    for (int i = 0; i < brain->LAYER_COUNT[0]; i++) {
        brain->node_array[0][i] = inputs[i];
    }
}

void updatelayer(int layernum, struct BrainHandler *brain) {
    if (layernum <= 0 || layernum >= brain->num_layers) {
        printf("layernum %d is out of range\n", layernum);
        return;
    }

    for (int nextlayerneuron = 0; nextlayerneuron < brain->LAYER_COUNT[layernum]; nextlayerneuron++) {
        float sum = 0.0f;
        for (int oldlayerneuron = 0; oldlayerneuron < brain->LAYER_COUNT[layernum-1]; oldlayerneuron++) {
            sum += brain->node_array[layernum-1][oldlayerneuron] * brain->weight_array[layernum-1][oldlayerneuron][nextlayerneuron];
        }
        brain->node_array[layernum][nextlayerneuron] = sigmoid(sum);
    }
}

#endif
