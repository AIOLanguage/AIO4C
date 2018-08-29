#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

//#define AIO_PROJECT_MEMORY_MANAGER

void *new_object(const unsigned size_of_object);

void *new_object_array(const unsigned number_of_elements, const unsigned size_of_object);

void *reallocate_object_array(
        void *object_array,
        const unsigned new_number_of_elements,
        const unsigned size_of_object
);

#ifdef AIO_PROJECT_MEMORY_MANAGER

typedef struct aio_project_memory_controller {
    size_t number_of_objects;
    size_t number_of_object_arrays;
} aio_project_memory_controller;

extern aio_project_memory_controller *project_memory_controller;

void inflate_aio_project_controller();

void free_aio_project_controller();

#endif

#endif //MEMORY_UTILS_H