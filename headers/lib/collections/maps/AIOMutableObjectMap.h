#ifndef AIO_MUTABLE_OBJECT_MAP_H
#define AIO_MUTABLE_OBJECT_MAP_H

#include "../../../lang/object/AIOObject.h"

typedef struct AIOMutableObjectMap {
    int *capacity;
    int *size;
    char **names;
    AIOObject **objects;
} AIOMutableObjectMap;

void createMutableMapOfAIOObject(AIOMutableObjectMap **objectMap);

void putInMutableMapOfObject(AIOMutableObjectMap *objectMap, AIOObject *object);

AIOObject *getObjectInMutableMapByName(AIOMutableObjectMap *objectMap, char *name);

#endif //AIO_MUTABLE_OBJECT_MAP_H