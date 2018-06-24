#ifndef AIO_VARIABLE_MAP_H
#define AIO_VARIABLE_MAP_H

#include "../../../lang/methods/variable/AIOVariable.h"

typedef struct AIOVariableMap {
    int *capacity;
    int *size;
    char **names;
    AIOVariable **variables;
} aio_variable_map;

void createAIOVariableMap(aio_variable_map **variableMap);

void putInAIOVariableInMap(aio_variable_map *variableMap, AIOVariable *variable);

AIOVariable *getAIOVariableInMapByName(aio_variable_map *variableMap, char *name);

#endif //AIO_VARIABLE_MAP_H