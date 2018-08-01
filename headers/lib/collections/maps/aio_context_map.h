#ifndef AIO_CONTEXT_MAP_H
#define AIO_CONTEXT_MAP_H

#include "../../utils/string_utils/string_utils.h"
#include "../../../lang/aio_context/aio_context.h"

typedef struct aio_context_map {
    int capacity;
    int size;
    const_string_array names;
    aio_context **objects;
} aio_context_map;

aio_context_map *new_aio_context_map();

void put_aio_context_in_map(aio_context_map *map, aio_context *context);

aio_context *get_aio_context_in_map_by_name(aio_context_map *context_map, const_string name);

void delete_aio_context_map(aio_context_map *context_map);

#endif //AIO_CONTEXT_MAP_H