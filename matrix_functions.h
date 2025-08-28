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

void* hadamard_multiply_int(int* in1, int* in2, int rowcount, int columncount) {
    void* outmatrix = calloc(rowcount * columncount, sizeof(int));
    for (int i = 0; i < rowcount; i++) {
        for (int j = 0; j < columncount; j++) {
            void* source1 = (char*)in1 + (i * columncount + j) * sizeof(int);
            void* source2 = (char*)in2 + (i * columncount + j) * sizeof(int);
            void* dest = (char*)outmatrix + (i * columncount + j) * sizeof(int);
            *(int*)dest = (*(int*)source1) * (*(int*)source2);
        }
    }
    return outmatrix;
}

void* hadamard_multiply_float(float* in1, float* in2, int rowcount, int columncount) {
    void* outmatrix = calloc(rowcount * columncount, sizeof(float));
    for (int i = 0; i < rowcount; i++) {
        for (int j = 0; j < columncount; j++) {
            void* source1 = (char*)in1 + (i * columncount + j) * sizeof(float);
            void* source2 = (char*)in2 + (i * columncount + j) * sizeof(float);
            void* dest = (char*)outmatrix + (i * columncount + j) * sizeof(float);
            *(float*)dest = (*(float*)source1) * (*(float*)source2);
        }
    }
    return outmatrix;
}

void* matrix_multiply_int(int* in1, int* in2, int row, int common, int col) {
    int* outmatrix = calloc(row * col, sizeof(int));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int sum = 0;
            for (int k = 0; k < common; k++) {
                sum += in1[i * common + k] * in2[k * col + j];
            }
            outmatrix[i * col + j] = sum;
        }
    }
    return outmatrix;
}

void* matrix_multiply_float(float* in1, float* in2, int row, int common, int col) {
    float* outmatrix = calloc(row * col, sizeof(float));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            float sum = 0;
            for (int k = 0; k < common; k++) {
                sum += in1[i * common + k] * in2[k * col + j];
            }
            outmatrix[i * col + j] = sum;
        }
    }
    return outmatrix;
}

#endif

/*
const int row = 2;
const int col = 3;

int matrix[row][col] = {
{1,2,3},
{4,5,6}
};

int elemsize = sizeof(int);

void* out = transpose(matrix, row, col, elemsize);

int (*matrix2d)[row] = (int (*)[row])out;

for (int i = 0; i < col; i++) {
for (int j = 0; j < row; j++) {
printf("%d ", matrix2d[i][j]);
}
printf("\n");
}
printf("\n");

void* out2 = scalar_multiply_int(matrix2d, col, row, 2);
void* out3 = scalar_multiply_float(matrix2d, col, row, 2);
int (*matrix2d2)[row] = (int (*)[row])out2;
float (*matrix2d3)[row] = (float (*)[row])out3;

for (int i = 0; i < col; i++) {
for (int j = 0; j < row; j++) {
printf("%d ", matrix2d2[i][j]);
}
printf("\n");
}

for (int i = 0; i < col; i++) {
for (int j = 0; j < row; j++) {
printf("%f ", matrix2d3[i][j]);
}
printf("\n");
}

    float fmatrix[row][col] = {
        {1,2,3},
        {4,5,6}
    };

    int imatrix[row][col] = {
        {1,2,3},
        {4,5,6}
    };

    void* hadf = hadamard_multiply_float(fmatrix, fmatrix, row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%f ", ((float*)hadf)[i * col + j]);
        }
        printf("\n");
    }

    void* hadi = hadamard_multiply_int(imatrix, imatrix, row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", ((int*)hadi)[i * col + j]);
        }
        printf("\n");
    }
*/