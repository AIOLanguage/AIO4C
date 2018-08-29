#include <malloc.h>
#include <mem.h>
#include <stdlib.h>
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"

void *new_object(const size_t size_of_object)
{
    void *object = calloc(1, size_of_object);
    if (object == NULL) {
        perror("Can'n allocate memory for object!");
        exit(1);
    }
    return object;
}

void *new_object_array(const size_t number_of_elements, const size_t size_of_object)
{
    void *object_array = calloc(number_of_elements, size_of_object);
    if (object_array == NULL) {
        perror("Can not allocate memory for object array!");
        exit(1);
    }
    return object_array;
}

void *reallocate_object_array(void *object_array, const size_t new_number_of_elements, const size_t size_of_object)
{
    object_array = realloc(object_array, new_number_of_elements * sizeof(size_of_object));
    if (object_array == NULL) {
        perror("Can not reallocate memory for object array!");
        exit(1);
    } else {
        return realloc(object_array, new_number_of_elements * size_of_object);
    }
}

void free_object(void *object)
{
    if (object != NULL) {
        free(object);
    }
}

#ifdef AIO_PROJECT_MEMORY_MANAGER

aio_project_memory_controller *project_memory_controller;

void inflate_aio_project_controller() {
    project_memory_controller = calloc(1, sizeof(aio_project_memory_controller));
}

void free_aio_project_controller() {

}

#endif