#ifndef AIO_CORE_H
#define AIO_CORE_H

#include "../../lib/collections/maps/aio_object_map.h"

typedef struct aio_core {
    aio_file_map *core_file_map;
} aio_core;

extern aio_core *core;

aio_core *init_aio_core();

void build_aio_file_and_put_in_core_file_map(const_string path);

void delete_aio_core();

#endif //AIO_CORE_H