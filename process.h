//
// Created by Pepper Scott on 29/8/2025.
//

#ifndef PROCESS_H
#define PROCESS_H

int* read_binary_input(int *out_length) {
    char* buffer = NULL;
    int capacity = 0;
    int length = 0;
    int c;

    printf("Input: ");
    while ((c = getchar()) != '\n' && c != EOF) {
        if (length >= capacity) {
            capacity = (capacity == 0) ? 16 : capacity * 2;
            buffer = realloc(buffer, capacity * sizeof(char));
            if (!buffer) {
                perror("realloc failed");
                exit(1);
            }
        }
        buffer[length++] = (char)c;
    }

    int* arr = malloc(length * sizeof(int));
    if (!arr) {
        perror("malloc failed");
        free(buffer);
        exit(1);
    }

    for (int i = 0; i < length; i++) {
        arr[i] = buffer[i] - '0';
    }

    free(buffer);
    *out_length = length;
    return arr;
}

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
