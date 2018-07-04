#ifndef AIO_METHOD_CONTAINER_H
#define AIO_METHOD_CONTAINER_H

#include "../../lib/collections/maps/aio_variable_map.h"

typedef struct aio_method_container {
    aio_variable_map *arg_map;
    aio_variable_map *variable_map;
} aio_method_container;

#endif //AIO_METHOD_CONTAINER_H