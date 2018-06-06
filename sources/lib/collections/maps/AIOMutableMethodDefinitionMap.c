#include <mem.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include "../../../../headers/lib/collections/maps/AIOMutableMethodDefinitionMap.h"

//Passed JUnitTests!
void createMutableMapOfDefinitions(AIOMutableMethodDefinitionMap **mutableMethodDefinitionMap) {
    //Create the same definition map:
    *mutableMethodDefinitionMap = malloc(sizeof(AIOMutableMethodDefinitionMap));
    //Create capacity:
    (*mutableMethodDefinitionMap)->capacity = malloc(sizeof(int));
    *(*mutableMethodDefinitionMap)->capacity = 2;
    //Create size:
    (*mutableMethodDefinitionMap)->size = malloc(sizeof(int));
    *(*mutableMethodDefinitionMap)->size = 0;
    //Create char capacity that equals 2:
    (*mutableMethodDefinitionMap)->names = malloc(2 * sizeof(char));
    //Create definitions that equals 2:
    (*mutableMethodDefinitionMap)->definitions = malloc(2 * sizeof(AIOMethodDefinition));
}

//Passed JUnitTests!
void updateMemoryInMutableMapOfDefinitions(AIOMutableMethodDefinitionMap *definitionMap) {
    if (*definitionMap->size + 1 == *definitionMap->capacity) {
        *definitionMap->capacity = *definitionMap->capacity * 2;
        definitionMap->names = realloc(definitionMap->names, *definitionMap->capacity * sizeof(char));
        definitionMap->definitions = realloc(definitionMap->definitions,
                                             *definitionMap->capacity * sizeof(AIOMethodDefinition));
    }
}

//Passed JUnitTests!
void putInMutableMapOfDefinitions(AIOMutableMethodDefinitionMap *definitionMap, AIOMethodDefinition *methodDefinition) {
    for (int i = 0; i < *definitionMap->size; ++i) {
        if (strcmp(definitionMap->names[i], methodDefinition->name) == 0) {
            printf("Cannot put AIOObject: %s in definition map", methodDefinition->name);
            exit(1);
        }
    }
    //Check to update:
    updateMemoryInMutableMapOfDefinitions(definitionMap);
    //Set key:
    definitionMap->names[*definitionMap->size] = malloc(strlen(methodDefinition->name));
    definitionMap->names[*definitionMap->size] = methodDefinition->name;
    //Set value:
    definitionMap->definitions[*definitionMap->size] = methodDefinition;
    *definitionMap->size = *definitionMap->size + 1;
}

//Passed JUnitTests!
AIOMethodDefinition *getMethodDefinitionInMutableMapByName(AIOMutableMethodDefinitionMap *definitionMap, char *name) {
    for (int i = 0; i < *definitionMap->size; ++i) {
        if (strcmp(definitionMap->names[i], name) == 0) {
            return definitionMap->definitions[i];
        }
    }
    printf("Cannot get AIOObject: %s in MutableList", name);
    exit(1);
}