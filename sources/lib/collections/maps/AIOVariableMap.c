#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/collections/maps/AIOVariableMap.h"

void createAIOVariableMap(AIOVariableMap **variableMap) {
    //Create the same variable map:
    *variableMap = calloc(1, sizeof(AIOVariableMap));
    if (*variableMap == NULL) {
        perror("can not allocate memory for aio variable map");
        exit(1);
    }
    //Create capacity:
    (*variableMap)->capacity = calloc(1, sizeof(int));
    if ((*variableMap)->capacity == NULL) {
        perror("can not allocate memory for capacity in aio variable map");
        exit(1);
    }
    *(*variableMap)->capacity = 2;
    //Create size:
    (*variableMap)->size = calloc(1, sizeof(int));
    if ((*variableMap)->size == NULL) {
        perror("can not allocate memory for size in aio variable map");
        exit(1);
    }
    *(*variableMap)->size = 0;
    //Create char capacity that equals 2:
    (*variableMap)->names = calloc(2, sizeof(char *));
    if ((*variableMap)->names == NULL) {
        perror("can not allocate memory for names in aio variable map");
        exit(1);
    }
    //Create definitions that equals 2:
    (*variableMap)->variables = calloc(2, sizeof(AIOVariable *));
    if ((*variableMap)->variables == NULL) {
        perror("can not allocate memory for variables in aio variable map");
        exit(1);
    }
}

//Passed JUnitTests!
void updateMemoryInVariableMapOfObjects(AIOVariableMap *variableMap) {
    if (*variableMap->size + 1 == *variableMap->capacity) {
        *variableMap->capacity = *variableMap->capacity * 2;
        variableMap->names = realloc(variableMap->names, *variableMap->capacity * sizeof(char *));
        variableMap->variables = realloc(variableMap->variables, *variableMap->capacity * sizeof(AIOVariable *));
    }
}

void putInAIOVariableInMap(AIOVariableMap *variableMap, AIOVariable *variable) {
    for (int i = 0; i < *variableMap->size; ++i) {
        if (strcmp(variableMap->names[i], variable->name) == 0) {
            perror("Cannot put AIOObject in definition map");
        }
    }
    //Check to update:
    updateMemoryInVariableMapOfObjects(variableMap);
    //Set key:
    variableMap->names[*variableMap->size] = malloc(strlen(variable->name));
    if (variableMap->names[*variableMap->size] == NULL) {
        perror("cannot allocate memory for names!");
    }
    variableMap->names[*variableMap->size] = variable->name;
    //Set value:
    variableMap->variables[*variableMap->size] = variable;
    *variableMap->size = *variableMap->size + 1;
}

AIOVariable *getAIOVariableInMapByName(AIOVariableMap *variableMap, char *name) {
    for (int i = 0; i < strlen(name); ++i) {
        if (strcmp(variableMap->names[i], name) == 0) {
            return variableMap->variables[i];
        }
    }
    perror("cannot get aio variable in map");
}