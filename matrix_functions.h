//
// Created by Pepper Scott on 27/8/2025.
//

#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H

void* transpose(const void* inmatrix, int rowcount, int columncount, int elemsize) {
    void* outmatrix = calloc(rowcount * columncount, elemsize);
    if (!outmatrix) return NULL;

    for (int i = 0; i < rowcount; i++) {
        for (int j = 0; j < columncount; j++) {
            const void* source = (const char*)inmatrix + (i * columncount + j) * elemsize;
            void* dest = (char*)outmatrix + (j * rowcount + i) * elemsize;
            memcpy(dest, source, elemsize);
        }
    }
    return outmatrix;
}

void* scalar_multiply_int(void* matrix, int rowcount, int columncount, float scalar) {
    void* outmatrix = calloc(rowcount * columncount, sizeof(int));
    for (int i = 0; i < rowcount; i++) {
        for (int j = 0; j < columncount; j++) {
            void* source = (char*)matrix + (i * columncount + j) * sizeof(int);
            void* dest = (char*)outmatrix + (i * columncount + j) * sizeof(int);
            *(int*)dest = (*(int*)source) * scalar;
        }
    }
    return outmatrix;
}

void* scalar_multiply_float(void* matrix, int rowcount, int columncount, float scalar) {
    void* outmatrix = calloc(rowcount * columncount, sizeof(float));
    for (int i = 0; i < rowcount; i++) {
        for (int j = 0; j < columncount; j++) {
            void* source = (char*)matrix + (i * columncount + j) * sizeof(float);
            void* dest = (char*)outmatrix + (i * columncount + j) * sizeof(float);
            *(float*)dest = (*(float*)source) * scalar;
        }
    }
    return outmatrix;
}

//void hadamard_multiply

#endif
