#include <mem.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include "../../../../headers/lib/collections/maps/aio_context_map.h"

aio_context_map *new_aio_context_map() {
    aio_context_map *object_map = calloc(1, sizeof(aio_context_map));
    object_map->capacity = 2;
    object_map->size = 0;
    //create char capacity that equals 2:
    object_map->names = calloc(2, sizeof(char *));
    //create definitions that equals 2:
    object_map->objects = calloc(2, sizeof(aio_file *));
    return object_map;
}

void update_memory_in_object_map(aio_context_map *object_map) {
    if (object_map->size + 1 == object_map->capacity) {
        object_map->capacity = object_map->capacity * 2;
        object_map->names = realloc(object_map->names, object_map->capacity * sizeof(char *));
        object_map->objects = realloc(object_map->objects, object_map->capacity * sizeof(aio_file *));
    }
}

void put_aio_context_in_map(aio_context_map *map, aio_context *context) {
    for (int i = 0; i < map->size; ++i) {
        if (strcmp(map->names[i], context->name) == 0) {
            perror("Cannot put aio_context in definition map");
            exit(1);
        }
    }
    update_memory_in_object_map(map);
    //Set key:
    map->names[map->size] = malloc(strlen(context->name));
    if (map->names[map->size] == NULL) {
        perror("cannot allocate memory for names!");
        exit(1);
    }
    map->names[map->size] = context->name;
    //Set value:
    map->objects[map->size] = context;
    map->size++;
}

aio_file *get_aio_context_in_map_by_name(aio_context_map *context_map, const_string name) {
    for (int i = 0; i < strlen(name); ++i) {
        if (strcmp(context_map->names[i], name) == 0) {
            return context_map->objects[i];
        }
    }
    return NULL;
}