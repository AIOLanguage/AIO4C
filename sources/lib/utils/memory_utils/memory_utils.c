#include <malloc.h>
#include <mem.h>
#include <stdlib.h>

void *new_object(const size_t size_of_object) {
    void *object = calloc(1, size_of_object);
    if (object == NULL) {
        perror("Can'n allocate memory for object!");
        exit(1);
    }
    return object;
}

void *new_object_array(const size_t number_of_elements, const size_t size_of_object) {
    void *object_array = calloc(number_of_elements, size_of_object);
    if (object_array == NULL) {
        perror("Can'n allocate memory for object array!");
        exit(1);
    }
}