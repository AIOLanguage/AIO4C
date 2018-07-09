#ifndef AIO_OBJECT_MAP_H
#define AIO_OBJECT_MAP_H

#include "../../../lang/aio_file/aio_file.h"

typedef struct aio_file_map {
    int capacity;
    int size;
    const_string_array names;
    aio_file **objects;
} aio_file_map;

aio_file_map *new_aio_file_map();

void put_aio_object_in_map(aio_file_map *set, aio_file *object);

aio_file *get_aio_file_in_map_by_name(aio_file_map *object_map, const_string name);

void delete_aio_object_map(aio_file_map *file_map);

#endif //AIO_OBJECT_MAP_H