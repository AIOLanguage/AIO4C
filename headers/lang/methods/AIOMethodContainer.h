#ifndef AIO_METHOD_CONTAINER_H
#define AIO_METHOD_CONTAINER_H

#include "../../lib/collections/maps/AIOVariableMap.h"

typedef struct AIOMethodContainer {
    aio_variable_map *argMap;
    aio_variable_map *variableMap;
} aio_method_container;

#endif //AIO_METHOD_CONTAINER_H