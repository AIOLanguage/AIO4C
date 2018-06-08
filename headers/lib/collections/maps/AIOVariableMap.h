#ifndef AIO_VARIABLE_MAP_H
#define AIO_VARIABLE_MAP_H

#include "../../../lang/methods/variable/AIOVariable.h"

typedef struct AIOVariableMap {
    int *capacity;
    int *size;
    char **names;
    AIOVariable **variables;
} AIOVariableMap;

void createAIOVariableMap(AIOVariableMap **variableMap);

void putAIOVariableInMap(AIOVariableMap *variableMap, AIOVariable *variable);

AIOVariable *getAIOVariableInMapByName(AIOVariableMap *variableMap, char *name);

#endif //AIO_VARIABLE_MAP_H