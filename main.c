#ifndef defaults
#define defaults
const float default_weight = 0.5f;
#endif

#include "imports.h"

int main(void) {

    int layer_neuron_nums[] = {2,10,4,4,1};

    struct BrainHandler *brain = init(layer_neuron_nums, sizeof(layer_neuron_nums)/sizeof(layer_neuron_nums[0]));
    const float inputs[] = {1.0f, 1.0f};
    setfirstlayer(inputs, brain);
    for (int layernum = 1; layernum < brain->num_layers; layernum++) {
        updatelayer(layernum, brain);
    }

    //print_weight(brain);
    print_node(brain);

    free_brain(brain);
    return 0;
}