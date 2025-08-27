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

#endif
