#ifndef AIO_VARIABLE_MAP_H
#define AIO_VARIABLE_MAP_H

#include "../../../lang/methods/variable/aio_variable.h"

typedef struct AIOVariableMap {
    int *capacity;
    int *size;
    char **names;
    aio_variable **variables;
} aio_variable_map;

void createAIOVariableMap(aio_variable_map **variableMap);

void putInAIOVariableInMap(aio_variable_map *variableMap, aio_variable *variable);

aio_variable *getAIOVariableInMapByName(aio_variable_map *variableMap, char *name);

#endif //AIO_VARIABLE_MAP_H