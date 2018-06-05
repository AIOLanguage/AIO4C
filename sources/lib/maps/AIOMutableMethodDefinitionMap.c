#include <mem.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include "../../../headers/lib/maps/AIOMutableMethodDefinitionMap.h"

void createMutableMapOfDefinitions(AIOMutableMethodDefinitionMap **mutableMethodDefinitionMap) {
    //Create the same definition map:
    *mutableMethodDefinitionMap = malloc(sizeof(AIOMutableMethodDefinitionMap));
    //Create capacity:
    (*mutableMethodDefinitionMap)->capacity = malloc(sizeof(int));
    *(*mutableMethodDefinitionMap)->capacity = 2;
    //Create size:
    (*mutableMethodDefinitionMap)->size = malloc(sizeof(int));
    *(*mutableMethodDefinitionMap)->size = 2;
    //Create char capacity that equals 2:
    (*mutableMethodDefinitionMap)->names = malloc(2 * sizeof(char));
    //Create definitions that equals 2:
    (*mutableMethodDefinitionMap)->definitions = malloc(2 * sizeof(AIOMethodDefinition));
}

void putInMutableMapOfDefinitions(AIOMutableMethodDefinitionMap *definitionMap,
                                  AIOMethodDefinition *methodDefinition) {
    //Set key with 32 chars:
    definitionMap->names[*definitionMap->size] = malloc(32 * sizeof(char));
    definitionMap->names[*definitionMap->size] = methodDefinition->name;
    //Set value:
    definitionMap->definitions[*definitionMap->size] = methodDefinition;
    definitionMap->size++;
}

AIOMethodDefinition *
getMethodDefinitionInMutableMapByName(AIOMutableMethodDefinitionMap *definitionMap, const char *name) {
    for (int i = 0; i < strlen(name); ++i) {
        if (strcmp(definitionMap->names[i], name) == 0) {
            return definitionMap->definitions[i];
        }
    }
    printf("Cannot get AIOObject: %s in MutableList", name);
    exit(1);
}