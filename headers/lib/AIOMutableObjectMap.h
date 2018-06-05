#ifndef AIO_AIO_MUTABLE_OBJECT_MAP_H
#define AIO_AIO_MUTABLE_OBJECT_MAP_H

#include "../lang/object/AIOObject.h"

typedef struct AIOMutableObjectMap {
    int size;
    char names[256][256];
    AIOObject objects[256];
} AIOMutableObjectMap;

AIOMutableObjectMap mutableMapOfObject();

void putInMutableMapOfObject(struct AIOMutableObjectMap *objectMap, struct AIOObject *aioObject);

AIOObject getObjectInMutableMapByName(struct AIOMutableObjectMap *objectMap, const char name[]);

#endif //AIO_AIO_MUTABLE_OBJECT_MAP_H