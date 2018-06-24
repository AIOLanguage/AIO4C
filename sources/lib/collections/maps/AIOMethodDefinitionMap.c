#include <mem.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include "../../../../headers/lib/collections/maps/AIOMethodDefinitionMap.h"

//Passed JUnitTests!
void createAIOMethodDefinitionMap(AIOMethodDefinitionMap **definitionMap) {
    //Create the same definition map:
    *definitionMap = calloc(1, sizeof(AIOMethodDefinitionMap));
    if (*definitionMap == NULL){
        perror("can not allocate memory for aio definition map");
        exit(1);
    }
    //Create capacity:
    (*definitionMap)->capacity = calloc(1, sizeof(int));
    if ((*definitionMap)->capacity == NULL){
        perror("can not allocate memory for capacity in aio definition map");
        exit(1);
    }
    *(*definitionMap)->capacity = 2;
    //Create size:
    (*definitionMap)->size = calloc(1, sizeof(int));
    if ((*definitionMap)->size == NULL){
        perror("can not allocate memory for size in aio definition map");
        exit(1);
    }
    *(*definitionMap)->size = 0;
    //Create char capacity that equals 2:
    (*definitionMap)->names = calloc(2, sizeof(char *));
    if ((*definitionMap)->names == NULL){
        perror("can not allocate memory for capacity in aio definition map");
        exit(1);
    }
    //Create definitions that equals 2:
    (*definitionMap)->definitions = calloc(2, sizeof(aio_method_definition*));
    if ((*definitionMap)->definitions == NULL){
        perror("can not allocate memory for definitions in aio variable map");
        exit(1);
    }
}

//Passed JUnitTests!
void updateMemoryInMutableMapOfDefinitions(AIOMethodDefinitionMap *definitionMap) {
    if (*definitionMap->size + 1 == *definitionMap->capacity) {
        *definitionMap->capacity = *definitionMap->capacity * 2;
        definitionMap->names = realloc(definitionMap->names, *definitionMap->capacity * sizeof(char));
        definitionMap->definitions = realloc(definitionMap->definitions,
                                             *definitionMap->capacity * sizeof(aio_method_definition));
    }
}

//Passed JUnitTests!
void putAIOMethodDefinitionInMap(AIOMethodDefinitionMap *definitionMap, aio_method_definition *methodDefinition) {
    for (int i = 0; i < *definitionMap->size; ++i) {
        if (strcmp(definitionMap->names[i], methodDefinition->name) == 0) {
            perror("AIODuplicate definition error!");
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
aio_method_definition *getAIOMethodDefinitionInMapByName(AIOMethodDefinitionMap *definitionMap, char *name) {
    for (int i = 0; i < *definitionMap->size; ++i) {
        if (strcmp(definitionMap->names[i], name) == 0) {
            return definitionMap->definitions[i];
        }
    }
    perror("can not get aio method definition in map!!!");
}