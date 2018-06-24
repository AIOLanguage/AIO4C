#include <mem.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include "../../../../headers/lib/collections/maps/aio_object_map.h"

//Passed JUnitTests!
void new_aio_object_map(aio_object_map **objectMap) {
    //Create the same definition map:
    *objectMap = calloc(1, sizeof(aio_object_map));
    if (*objectMap == NULL) {
        perror("cannot allocate memory for aio_object!");
    }
    //Create capacity:
    (*objectMap)->capacity = calloc(1, sizeof(int));
    if ((*objectMap)->capacity == NULL) {
        perror("cannot allocate memory for capacity!");
    }
    *(*objectMap)->capacity = 2;
    //Create size:
    (*objectMap)->size = calloc(1, sizeof(int));
    if ((*objectMap)->size == NULL) {
        perror("cannot allocate memory for size!");
    }
    *(*objectMap)->size = 0;
    //Create char capacity that equals 2:
    (*objectMap)->names = calloc(2, sizeof(char *));
    if ((*objectMap)->names == NULL) {
        perror("cannot allocate memory for names!");
    }
    //Create definitions that equals 2:
    (*objectMap)->objects = calloc(2, sizeof(aio_object *));
    if ((*objectMap)->objects == NULL) {
        perror("cannot allocate memory for objects!");
    }
}

//Passed JUnitTests!
void updateMemoryInMutableMapOfObjects(aio_object_map *objectMap) {
    if (*objectMap->size + 1 == *objectMap->capacity) {
        *objectMap->capacity = *objectMap->capacity * 2;
        objectMap->names = realloc(objectMap->names, *objectMap->capacity * sizeof(char *));
        objectMap->objects = realloc(objectMap->objects, *objectMap->capacity * sizeof(aio_object *));
    }
}

//Passed JUnitTests!
void put_aio_object_in_map(aio_object_map *object_map, aio_object *object) {
    for (int i = 0; i < *object_map->size; ++i) {
        if (strcmp(object_map->names[i], object->name) == 0) {
            perror("Cannot put aio_object in definition map");
        }
    }
    //Check to update:
    updateMemoryInMutableMapOfObjects(object_map);
    //Set key:
    object_map->names[*object_map->size] = malloc(strlen(object->name));
    if (object_map->names[*object_map->size] == NULL) {
        perror("cannot allocate memory for names!");
    }
    object_map->names[*object_map->size] = object->name;
    //Set value:
    object_map->objects[*object_map->size] = object;
    *object_map->size = *object_map->size + 1;
}

//Passed JUnitTests!
aio_object *get_aio_object_in_map_by_name(aio_object_map *object_map, char *name) {
    for (int i = 0; i < strlen(name); ++i) {
        if (strcmp(object_map->names[i], name) == 0) {
            return object_map->objects[i];
        }
    }
    return NULL;
}

/*
 * /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * int main() {
    aio_object_map* objectMap;
    new_aio_object_map(&objectMap);
    printf("%d", *objectMap->size);

    aio_method_definition_map* definitionMap;
    new_aio_method_definition_map(&definitionMap);

    aio_method_manager* aioMethodManager;
    new_aio_method_manager(&aioMethodManager, definitionMap);

    aio_object* aioObject;
    new_aio_object(&aioObject, aioMethodManager, "starter");

    put_aio_object_in_map(objectMap, aioObject);
    aio_object* o = get_aio_object_in_map_by_name(objectMap, "starter");
    printf("%d", *o->method_manager->hasMain);

    return 0;
}
 */