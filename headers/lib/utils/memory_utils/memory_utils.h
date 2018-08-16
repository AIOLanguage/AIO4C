#include <malloc.h>
#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

void *new_object(const size_t size_of_object);

void *new_object_array(const size_t number_of_elements, const size_t size_of_object);

#endif //MEMORY_UTILS_H