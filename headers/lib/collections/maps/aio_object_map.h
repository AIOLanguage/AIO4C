#ifndef AIO_OBJECT_MAP_H
#define AIO_OBJECT_MAP_H

#include "../../../lang/object/aio_object.h"

typedef struct aio_object_map {
    int capacity;
    int size;
    char **names;
    aio_object **objects;
} aio_object_map;

aio_object_map* new_aio_object_map();

void put_aio_object_in_map(aio_object_map *object_map, aio_object *object);

aio_object *get_aio_object_in_map_by_name(aio_object_map *object_map, char *name);

#endif //AIO_OBJECT_MAP_H