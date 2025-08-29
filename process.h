//
// Created by Pepper Scott on 29/8/2025.
//

#ifndef PROCESS_H
#define PROCESS_H

void process(struct BrainHandler *brain, float* inputs, int inputlength, const float* test) {
    int testq = test!=NULL;

    setfirstlayer(inputs, brain);
    updatebrain(brain);

    if (testq) {
        gradient(brain, test);
        change_weights_and_biases(brain);
    } else {
        printf("Output: ");
        for (int i = 0; i < brain->outputneurons; i++) {
            printf("%f ", brain->output_array[i]);
        }
        printf("\n");
    }
}
#endif
