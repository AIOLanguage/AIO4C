#include <mem.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include "../../../headers/lib/maps/AIOMutableMethodDefinitionMap.h"

AIOMutableMethodDefinitionMap mutableMapOfDefinitions() {
    struct AIOMutableMethodDefinitionMap methodDefinitionMap = {.size = 0};
    return methodDefinitionMap;
}

void putInMutableMapOfDefinitions(AIOMutableMethodDefinitionMap *definitionMap,
                                  AIOMethodDefinition *methodDefinition) {
    //Set key:
    strcpy(definitionMap->names[definitionMap->size], methodDefinition->name);
    //Set value:
    definitionMap->definitions[definitionMap->size] = methodDefinition;
    definitionMap->size++;
}

AIOMethodDefinition* getMethodDefinitionInMutableMapByName(AIOMutableMethodDefinitionMap *definitionMap
        , const char *name) {
    for (int i = 0; i < strlen(name); ++i) {
        if (strcmp(definitionMap->names[i], name) == 0) {
            return definitionMap->definitions[i];
        }
    }
    printf("Cannot get AIOObject: %s in MutableList", name);
    exit(1);
}