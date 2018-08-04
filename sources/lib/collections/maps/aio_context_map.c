#include <mem.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include "../../../../headers/lib/collections/maps/aio_context_map.h"

aio_context_map *new_aio_context_map() {
    aio_context_map *map = calloc(1, sizeof(aio_context_map));
    map->capacity = 2;
    map->size = 0;
    //create char capacity that equals 2:
    map->names = calloc(2, sizeof(char *));
    //create definitions that equals 2:
    map->contexts = calloc(2, sizeof(aio_context *));
    return map;
}

void update_memory_in_object_map(aio_context_map *map) {
    if (map->size + 1 == map->capacity) {
        map->capacity = map->capacity * 2;
        map->names = realloc(map->names, map->capacity * sizeof(char *));
        map->contexts = realloc(map->contexts, map->capacity * sizeof(aio_context *));
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
    //Set aio_value:
    map->contexts[map->size] = context;
    map->size++;
}

aio_context *get_aio_context_in_map_by_name(aio_context_map *context_map, const_string name) {
    for (int i = 0; i < strlen(name); ++i) {
        if (strcmp(context_map->names[i], name) == 0) {
            return context_map->contexts[i];
        }
    }
    return NULL;
}