#include <mem.h>
#include <process.h>
#include <stdio.h>
#include "../../headers/lib/AIOMutableObjectMap.h"

//Passed JUnitTests!
AIOMutableObjectMap mutableMapOfObject() {
    struct AIOMutableObjectMap mutableObjectMap = {.size = 0};
    return mutableObjectMap;
}

//Passed JUnitTests!
void putInMutableMapOfObject(struct AIOMutableObjectMap *objectMap, struct AIOObject *aioObject) {
    const int index = objectMap->size;
    //Set key:
    strcpy(objectMap->names[index], aioObject->name);
    //Set value:
    objectMap->objects[index] = *aioObject;
    objectMap->size++;
}

//Passed JUnitTests!
AIOObject getObjectInMutableMapByName(struct AIOMutableObjectMap *objectMap, const char name[]) {
    for (int i = 0; i < strlen(name); ++i) {
        if (strcmp(objectMap->names[i], name) == 0){
            return objectMap->objects[i];
        }
    }
    printf("Cannot get AIOObject: %s in MutableList", name);
    exit(1);
}