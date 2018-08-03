#ifndef AIO_CORE_H
#define AIO_CORE_H

#include "../../lib/collections/maps/aio_context_map.h"
#include "../../lib/utils/string_utils/string_utils.h"
#include "../../lib/collections/sets/string_set.h"

#define NUMBER_OF_CORE_TYPES 5

typedef struct aio_core {
    aio_context_map *core_context_map;
    //유형 포함 (Keep types):
    string_set *aio_type_set;
} aio_core;

extern aio_core *core;

void inflate_aio_core();

void inflate_aio_context_and_put_in_core(const_string path);

boolean contains_aio_type_in_set(string string);

void destroy_aio_core();

#endif //AIO_CORE_H