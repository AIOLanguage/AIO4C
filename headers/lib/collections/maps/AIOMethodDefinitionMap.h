#ifndef AIO_METHOD_DEFINITION_MAP_H
#define AIO_METHOD_DEFINITION_MAP_H

#include "../../../lang/methods/methodDefinition/aio_method_definition.h"

typedef struct AIOMethodDefinitionMap {
    int *capacity;
    int *size;
    char **names;
    aio_method_definition **definitions;
} AIOMethodDefinitionMap;

void createAIOMethodDefinitionMap(AIOMethodDefinitionMap **definitionMap);

void putAIOMethodDefinitionInMap(AIOMethodDefinitionMap *definitionMap, aio_method_definition *methodDefinition);

aio_method_definition *getAIOMethodDefinitionInMapByName(AIOMethodDefinitionMap *definitionMap, char *name);

#endif //AIO_METHOD_DEFINITION_MAP_H