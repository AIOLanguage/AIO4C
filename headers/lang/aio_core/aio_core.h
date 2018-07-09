#ifndef AIO_CORE_H
#define AIO_CORE_H

#include "../../lib/collections/maps/aio_file_map.h"
#include "../../lib/utils/string_utils/string_utils.h"
#include "../../lib/collections/sets/string_set.h"

typedef struct aio_core {
    aio_file_map *core_file_map;
    string_set *aio_type_set;
} aio_core;

extern aio_core *core;

aio_core *init_aio_core();

void build_aio_file_and_put_in_core_file_map(const_string path);

boolean contains_aio_type_in_set(const_string string);

void delete_aio_core();

#endif //AIO_CORE_H