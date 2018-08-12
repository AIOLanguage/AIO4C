#include <malloc.h>

void *new_object(size_t size_of_object) {
    return calloc(1, size_of_object);
}