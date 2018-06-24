#ifndef AIO_OBJECT_MAP_H
#define AIO_OBJECT_MAP_H

#include "../../../lang/object/AIOObject.h"

typedef struct AIOObjectMap {
    int *capacity;
    int *size;
    char **names;
    aio_object **objects;
} AIOObjectMap;

void createAIOObjectMap(AIOObjectMap **objectMap);

void putAIOObjectInMap(AIOObjectMap *objectMap, aio_object *object);

aio_object *get_aio_object_in_map_by_name(AIOObjectMap *objectMap, char *name);

#endif //AIO_OBJECT_MAP_H