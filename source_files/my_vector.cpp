#include <stdio.h>
#include "../headers/my_vector.h"
#include <assert.h>
#include "../headers/systemdata.h"
#include <string.h>

const int INCREASE_COEFF   = 2;
const int VECTOR_INIT_SIZE = 8;

enum VecChangeSize {
    ChangeSizeRaise = 0,
    ChangeSizeCut   = 1,
};

static int resize(Vector *vec, VecChangeSize action);
static int verifyVector(Vector *vec);

int vectorCtor(Vector *vec, size_t size, size_t element_size) {

    assert(vec);

    vec->data = calloc (size, element_size);
    if (!vec->data) return NO_MEMORY;

    vec->size = 0;
    vec->capacity = size;
    vec->element_size = element_size;

    return SUCCESS;
}

int vectorDtor(Vector *vec) {

    assert(vec);

    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
    vec->element_size = 0;

    return SUCCESS;
}

int pushBack(Vector *vec, void *buffer) {

    assert(vec);

    if (verifyVector(vec) != SUCCESS)
        return ERROR;

    if (vec->size >= vec->capacity) {
        if (resize(vec, ChangeSizeRaise) != SUCCESS)
            return NO_MEMORY;
    }

    memcpy(vec->data + vec->size++ * vec->element_size, buffer, vec->element_size);

    return SUCCESS;
}

int pop(Vector *vec, void *buffer) {

    assert(vec);

    if (verifyVector(vec) != SUCCESS)
        return ERROR;

    if (vec->size - 1 < 0) {
        printf(RED "vector error: " END_OF_COLOR "empty. Unable to pop value\n");
        return NULL;
    }

    memcpy(buffer, vec->data + --vec->size * vec->element_size, vec->element_size);

    if (vec->capacity > VECTOR_INIT_SIZE && vec->capacity - vec->size > vec->capacity - vec->capacity / INCREASE_COEFF) {
        if (resize(vec, ChangeSizeCut) != SUCCESS)
            return NO_MEMORY;
    }

    return SUCCESS;

}
static int resize(Vector *vec, VecChangeSize action) {

    assert(vec);

    if (action == ChangeSizeRaise) {
        vec->capacity *= INCREASE_COEFF;
    }
    else {
        vec->capacity /= INCREASE_COEFF;
    }

    void *tmp = realloc (vec->data, vec->element_size * vec->capacity);
    if (!tmp)   return NO_MEMORY;

    vec->data = tmp;

    memset(vec->data + vec->size, 0, (vec->capacity - vec->size) * vec->element_size);

    return SUCCESS;
}

static int verifyVector(Vector *vec) {

    assert(vec);

    if (!vec->data) {
        printf(RED "Vector data: NULL" END_OF_COLOR "\n");
        return ERROR;
    }
    if (vec->size >= vec->capacity) {
        printf(RED "Vector: incorrect size or capacity" END_OF_COLOR "\n");
        return ERROR;
    }

    return SUCCESS;
}