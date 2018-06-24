#include <mem.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include "../../../../headers/lib/collections/maps/AIOObjectMap.h"

//Passed JUnitTests!
void createAIOObjectMap(AIOObjectMap **objectMap) {
    //Create the same definition map:
    *objectMap = calloc(1, sizeof(AIOObjectMap));
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
void updateMemoryInMutableMapOfObjects(AIOObjectMap *objectMap) {
    if (*objectMap->size + 1 == *objectMap->capacity) {
        *objectMap->capacity = *objectMap->capacity * 2;
        objectMap->names = realloc(objectMap->names, *objectMap->capacity * sizeof(char *));
        objectMap->objects = realloc(objectMap->objects, *objectMap->capacity * sizeof(aio_object *));
    }
}

//Passed JUnitTests!
void putAIOObjectInMap(AIOObjectMap *objectMap, aio_object *object) {
    for (int i = 0; i < *objectMap->size; ++i) {
        if (strcmp(objectMap->names[i], object->name) == 0) {
            perror("Cannot put aio_object in definition map");
        }
    }
    //Check to update:
    updateMemoryInMutableMapOfObjects(objectMap);
    //Set key:
    objectMap->names[*objectMap->size] = malloc(strlen(object->name));
    if (objectMap->names[*objectMap->size] == NULL) {
        perror("cannot allocate memory for names!");
    }
    objectMap->names[*objectMap->size] = object->name;
    //Set value:
    objectMap->objects[*objectMap->size] = object;
    *objectMap->size = *objectMap->size + 1;
}

//Passed JUnitTests!
aio_object *get_aio_object_in_map_by_name(AIOObjectMap *objectMap, char *name) {
    for (int i = 0; i < strlen(name); ++i) {
        if (strcmp(objectMap->names[i], name) == 0) {
            return objectMap->objects[i];
        }
    }
    return NULL;
}

/*
 * /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * int main() {
    AIOObjectMap* objectMap;
    createAIOObjectMap(&objectMap);
    printf("%d", *objectMap->size);

    AIOMethodDefinitionMap* definitionMap;
    createAIOMethodDefinitionMap(&definitionMap);

    AIOMethodManager* aioMethodManager;
    createAIOMethodManager(&aioMethodManager, definitionMap);

    aio_object* aioObject;
    createAIOObject(&aioObject, aioMethodManager, "starter");

    putAIOObjectInMap(objectMap, aioObject);
    aio_object* o = get_aio_object_in_map_by_name(objectMap, "starter");
    printf("%d", *o->methodManager->hasMain);

    return 0;
}
 */