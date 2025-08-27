//
// Created by Pepper Scott on 27/8/2025.
//

#pragma once

#ifndef WEIGHT_BIAS_DELTA_H
#define WEIGHT_BIAS_DELTA_H

void reset_weight_bias_delta(struct BrainHandler *brain) {
    for (int layernum = 0; layernum < brain->num_layers; layernum++) {
        for (int layerneuron = 0; layerneuron < brain->LAYER_COUNT[layernum]; layerneuron++) {
            brain->bias_array[layernum][layerneuron] = 0.0f;
            brain->delta_array[layernum][layerneuron] = 0.0f;
        }
    }
}

void update_weight_delta(struct BrainHandler *brain) {

}

#endif
