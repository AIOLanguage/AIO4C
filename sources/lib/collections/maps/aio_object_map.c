#include <mem.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include "../../../../headers/lib/collections/maps/aio_object_map.h"

//Passed JUnitTests!
aio_file_map *new_aio_object_map() {
    //Create the same definition map:
    aio_file_map *object_map = calloc(1, sizeof(aio_file_map));
    if (object_map == NULL) {
        perror("cannot allocate memory for aio_file!");
        exit(1);
    }
    //Create capacity:
    object_map->capacity = 2;
    //Create size:
    object_map->size = 0;
    //Create char capacity that equals 2:
    object_map->names = calloc(2, sizeof(char *));
    if (object_map->names == NULL) {
        perror("cannot allocate memory for names!");
        exit(1);
    }
    //Create definitions that equals 2:
    object_map->objects = calloc(2, sizeof(aio_file *));
    if (object_map->objects == NULL) {
        perror("cannot allocate memory for objects!");
        exit(1);
    }
    return object_map;
}

//Passed JUnitTests!
void update_memory_in_object_map(aio_file_map *object_map) {
    if (object_map->size + 1 == object_map->capacity) {
        object_map->capacity = object_map->capacity * 2;
        object_map->names = realloc(object_map->names, object_map->capacity * sizeof(char *));
        object_map->objects = realloc(object_map->objects, object_map->capacity * sizeof(aio_file *));
    }
}

//Passed JUnitTests!
void put_aio_object_in_map(aio_file_map *object_map, aio_file *object) {
    for (int i = 0; i < object_map->size; ++i) {
        if (strcmp(object_map->names[i], object->name) == 0) {
            perror("Cannot put aio_file in definition map");
            exit(1);
        }
    }
    //Check to update:
    update_memory_in_object_map(object_map);
    //Set key:
    object_map->names[object_map->size] = malloc(strlen(object->name));
    if (object_map->names[object_map->size] == NULL) {
        perror("cannot allocate memory for names!");
        exit(1);
    }
    object_map->names[object_map->size] = object->name;
    //Set value:
    object_map->objects[object_map->size] = object;
    object_map->size++;
}

//Passed JUnitTests!
aio_file *get_aio_object_in_map_by_name(aio_file_map *object_map, char *name) {
    for (int i = 0; i < strlen(name); ++i) {
        if (strcmp(object_map->names[i], name) == 0) {
            return object_map->objects[i];
        }
    }
    return NULL;
}