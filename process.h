//
// Created by Pepper Scott on 29/8/2025.
//

#ifndef PROCESS_H
#define PROCESS_H

void* process(struct BrainHandler *brain, float* inputs, int inputlength, const float* test) {
    int testq = test!=NULL;
    printf("testing? %d\n", testq);
    //printf

    setfirstlayer(inputs, brain);
    updatebrain(brain);

    printf("\n");

    if (testq) {
        gradient(brain, test);
    }
}
#endif
