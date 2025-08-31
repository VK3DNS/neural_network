//
// Created by Pepper Scott on 29/8/2025.
//

#ifndef PROCESS_H
#define PROCESS_H

double* read_binary_input(const int* out_length) {
    char* buffer = NULL;
    int capacity = 0;
    int length = 0;
    double c;

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

    double* arr = malloc(length * sizeof(double));
    if (!arr) {
        perror("malloc failed");
        free(buffer);
        exit(1);
    }

    for (int i = 0; i < length; i++) {
        arr[i] = buffer[i] - '0';
    }

    free(buffer);
    return arr;
}

void process(struct BrainHandler *brain, double* inputs, int inputlength, const double* test, int testcase) {
    int testq = test!=NULL;

    brain->epoch = testcase;

    setfirstlayer(inputs, brain);
    updatebrain(brain);

    if (testq) {
        /*
        print_weight(brain);
        printf("\n\n");
        print_bias(brain);
        printf("\n\n");
        print_error(brain);
        */

        gradient(brain, test);
        change_weights_and_biases(brain);
    } else {
        double bestoutput = -1;
        int bestoutputcount = -1;
        //printf("Output: ");
        for (int i = 0; i < brain->outputneurons; i++) {
            printf("%f ", brain->output_array[i]);
            if (brain->output_array[i] > bestoutput) {
                bestoutput = brain->output_array[i];
                bestoutputcount = i;
            }
        }
        printf("\npredicted: %d", bestoutputcount);
        printf("\n");
    }
}
#endif
