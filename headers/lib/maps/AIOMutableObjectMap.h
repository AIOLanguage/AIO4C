#ifndef AIO_AIO_MUTABLE_OBJECT_MAP_H
#define AIO_AIO_MUTABLE_OBJECT_MAP_H

#include "../../lang/object/AIOObject.h"

typedef struct AIOMutableObjectMap {
    int size;
    char **names;
    AIOObject **objects;
} AIOMutableObjectMap;

void createMutableMapOfObject(AIOMutableObjectMap* mutableObjectMap);

void putInMutableMapOfObject(struct AIOMutableObjectMap *objectMap, struct AIOObject *aioObject);

AIOObject* getObjectInMutableMapByName(struct AIOMutableObjectMap *objectMap, const char name[]);

#endif //AIO_AIO_MUTABLE_OBJECT_MAP_H