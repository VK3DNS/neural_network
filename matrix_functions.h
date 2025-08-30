//
// Created by Pepper Scott on 27/8/2025.
//

#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H

double* transpose(const double* inmatrix, int rowcount, int columncount) {
    double* out = (double*)malloc(sizeof(double) * rowcount * columncount);

    for (int row = 0; row < rowcount; row++) {
        for (int col = 0; col < columncount; col++) {
            out[col * rowcount + row] = inmatrix[row * columncount + col];
        }
    }

    return out;
}

void* scalar_multiply(void* matrix, int rowcount, int columncount, double scalar) {
    void* outmatrix = calloc(rowcount * columncount, sizeof(double));
    for (int i = 0; i < rowcount; i++) {
        for (int j = 0; j < columncount; j++) {
            void* source = (char*)matrix + (i * columncount + j) * sizeof(double);
            void* dest = (char*)outmatrix + (i * columncount + j) * sizeof(double);
            *(double*)dest = (*(double*)source) * scalar;
        }
    }
    return outmatrix;
}

double* hadamard_multiply(double* in1, double* in2, int rowcount, int columncount) {
    int size = rowcount * columncount;
    double* outmatrix = calloc(size, sizeof(double));
    if (!outmatrix) return NULL;

    for (int i = 0; i < size; i++) {
        outmatrix[i] = in1[i] * in2[i];
    }

    return outmatrix;
}


void* matrix_multiply(double* in1, double* in2, int row, int common, int col) {
    double* outmatrix = calloc(row * col, sizeof(double));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            double sum = 0;
            for (int k = 0; k < common; k++) {
                sum += in1[i * common + k] * in2[k * col + j];
            }
            outmatrix[i * col + j] = sum;
        }
    }
    return outmatrix;
}

#endif