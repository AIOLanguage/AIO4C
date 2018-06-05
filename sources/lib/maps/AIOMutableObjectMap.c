#include <mem.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include "../../../headers/lib/maps/AIOMutableObjectMap.h"

//Passed JUnitTests!
void createMutableMapOfObject(AIOMutableObjectMap *mutableObjectMap) {
    mutableObjectMap = malloc(sizeof(AIOMutableObjectMap));
    mutableObjectMap->size = 0;
}

//Passed JUnitTests!
void putInMutableMapOfObject(struct AIOMutableObjectMap *objectMap, struct AIOObject *aioObject) {
    const int index = objectMap->size;
    //Set key:
    strcpy(objectMap->names[index], aioObject->name);
    //Set value:
    objectMap->objects[index] = aioObject;
    objectMap->size++;
}

//Passed JUnitTests!
AIOObject *getObjectInMutableMapByName(struct AIOMutableObjectMap *objectMap, const char name[]) {
    for (int i = 0; i < strlen(name); ++i) {
        if (strcmp(objectMap->names[i], name) == 0) {
            return objectMap->objects[i];
        }
    }
    printf("Cannot get AIOObject: %s in MutableList", name);
    exit(1);
}