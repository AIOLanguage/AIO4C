#ifndef AIO_OBJECT_MAP_H
#define AIO_OBJECT_MAP_H

#include "../../../lang/object/AIOObject.h"

typedef struct AIOObjectMap {
    int *capacity;
    int *size;
    char **names;
    AIOObject **objects;
} AIOObjectMap;

void createAIOObjectMap(AIOObjectMap **objectMap);

void putAIOObjectInMap(AIOObjectMap *objectMap, AIOObject *object);

AIOObject *getAIOObjectInMapByName(AIOObjectMap *objectMap, char *name);

#endif //AIO_OBJECT_MAP_H