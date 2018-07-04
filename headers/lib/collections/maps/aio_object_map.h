#ifndef AIO_OBJECT_MAP_H
#define AIO_OBJECT_MAP_H

#include "../../../lang/object/aio_file.h"

typedef struct aio_object_map {
    int capacity;
    int size;
    char **names;
    aio_file **objects;
} aio_file_map;

aio_file_map* new_aio_object_map();

void put_aio_object_in_map(aio_file_map *object_map, aio_file *object);

aio_file *get_aio_object_in_map_by_name(aio_file_map *object_map, char *name);

#endif //AIO_OBJECT_MAP_H