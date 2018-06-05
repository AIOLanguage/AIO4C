#ifndef AIO_AIO_MUTABLE_METHOD_DEFINITION_MAP_H
#define AIO_AIO_MUTABLE_METHOD_DEFINITION_MAP_H

#include "../../lang/methods/methodDefinition/AIOMethodDefinition.h"

typedef struct AIOMutableMethodDefinitionMap {
    int* capacity;
    int* size;
    char **names;
    AIOMethodDefinition **definitions;
} AIOMutableMethodDefinitionMap;

void createMutableMapOfDefinitions(AIOMutableMethodDefinitionMap** mutableMethodDefinitionMap);

void putInMutableMapOfDefinitions(struct AIOMutableMethodDefinitionMap *definitionMap,
                                  struct AIOMethodDefinition *methodDefinition);

AIOMethodDefinition* getMethodDefinitionInMutableMapByName(AIOMutableMethodDefinitionMap *definitionMap,
                                                          const char *name);

#endif //AIO_AIO_MUTABLE_METHOD_DEFINITION_MAP_H