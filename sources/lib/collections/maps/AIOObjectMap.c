#include <mem.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include "../../../../headers/lib/collections/maps/AIOObjectMap.h"

//Passed JUnitTests!
void createAIOObjectMap(AIOObjectMap **objectMap) {
    //Create the same definition map:
    *objectMap = malloc(sizeof(AIOObjectMap));
    //Create capacity:
    (*objectMap)->capacity = malloc(sizeof(int));
    *(*objectMap)->capacity = 2;
    //Create size:
    (*objectMap)->size = malloc(sizeof(int));
    *(*objectMap)->size = 0;
    //Create char capacity that equals 2:
    (*objectMap)->names = malloc(2 * sizeof(char));
    //Create definitions that equals 2:
    (*objectMap)->objects = malloc(2 * sizeof(AIOObject));
}

//Passed JUnitTests!
void updateMemoryInMutableMapOfObjects(AIOObjectMap *objectMap) {
    if (*objectMap->size + 1 == *objectMap->capacity) {
        *objectMap->capacity = *objectMap->capacity * 2;
        objectMap->names = realloc(objectMap->names, *objectMap->capacity * sizeof(char));
        objectMap->objects = realloc(objectMap->objects, *objectMap->capacity * sizeof(AIOObject));
    }
}


//Passed JUnitTests!
void putAIOObjectInMap(AIOObjectMap *objectMap, AIOObject *object) {
    for (int i = 0; i < *objectMap->size; ++i) {
        if (strcmp(objectMap->names[i], object->name) == 0) {
            printf("Cannot put AIOObject: %s in definition map", object->name);
            exit(1);
        }
    }
    //Check to update:
    updateMemoryInMutableMapOfObjects(objectMap);
    //Set key:
    objectMap->names[*objectMap->size] = malloc(strlen(object->name));
    objectMap->names[*objectMap->size] = object->name;
    //Set value:
    objectMap->objects[*objectMap->size] = object;
    *objectMap->size = *objectMap->size + 1;
}

//Passed JUnitTests!
AIOObject *getAIOObjectInMapByName(AIOObjectMap *objectMap, char *name) {
    for (int i = 0; i < strlen(name); ++i) {
        if (strcmp(objectMap->names[i], name) == 0) {
            return objectMap->objects[i];
        }
    }
    printf("Cannot get AIOObject: %s in MutableList", name);
    exit(1);
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

    AIOObject* aioObject;
    createAIOObject(&aioObject, aioMethodManager, "starter");

    putAIOObjectInMap(objectMap, aioObject);
    AIOObject* o = getAIOObjectInMapByName(objectMap, "starter");
    printf("%d", *o->methodManager->hasMain);

    return 0;
}
 */