#ifndef AIO_METHOD_DEFINITION_MAP_H
#define AIO_METHOD_DEFINITION_MAP_H

#include "../../../lang/methods/methodDefinition/AIOMethodDefinition.h"

typedef struct AIOMethodDefinitionMap {
    int *capacity;
    int *size;
    char **names;
    AIOMethodDefinition **definitions;
} AIOMethodDefinitionMap;

void createAIOMethodDefinitionMap(AIOMethodDefinitionMap **definitionMap);

void putAIOMethodDefinitionInMap(AIOMethodDefinitionMap *definitionMap, AIOMethodDefinition *methodDefinition);

AIOMethodDefinition *getAIOMethodDefinitionInMapByName(AIOMethodDefinitionMap *definitionMap, char *name);

#endif //AIO_METHOD_DEFINITION_MAP_H