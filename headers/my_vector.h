#ifndef VECTOR_CPU
#define VECTOR_CPU

#include <stdio.h>

struct Vector {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
};

int vectorCtor(Vector *vec, size_t size, size_t element_size);
int vectorDtor(Vector *vec);
int pushBack(Vector *vec, void *buffer);
int pop(Vector *vec, void *buffer);

#endif