#ifndef AIO_METHOD_CONTAINER_H
#define AIO_METHOD_CONTAINER_H

#include "../../lib/collections/maps/AIOVariableMap.h"

typedef struct AIOMethodContainer {
    AIOVariableMap *argMap;
    AIOVariableMap *variableMap;
} AIOMethodContainer;

#endif //AIO_METHOD_CONTAINER_H