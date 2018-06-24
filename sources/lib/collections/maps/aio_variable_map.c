#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/collections/maps/aio_variable_map.h"

void new_aio_variable_map(aio_variable_map **variableMap) {
    //Create the same variable map:
    *variableMap = calloc(1, sizeof(aio_variable_map));
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
    (*variableMap)->variables = calloc(2, sizeof(aio_variable *));
    if ((*variableMap)->variables == NULL) {
        perror("can not allocate memory for variables in aio variable map");
        exit(1);
    }
}

//Passed JUnitTests!
void updateMemoryInVariableMapOfObjects(aio_variable_map *variableMap) {
    if (*variableMap->size + 1 == *variableMap->capacity) {
        *variableMap->capacity = *variableMap->capacity * 2;
        variableMap->names = realloc(variableMap->names, *variableMap->capacity * sizeof(char *));
        variableMap->variables = realloc(variableMap->variables, *variableMap->capacity * sizeof(aio_variable *));
    }
}

void put_in_aio_variable_in_map(aio_variable_map *variable_map, aio_variable *variable) {
    for (int i = 0; i < *variable_map->size; ++i) {
        if (strcmp(variable_map->names[i], variable->name) == 0) {
            perror("Cannot put aio_object in definition map");
        }
    }
    //Check to update:
    updateMemoryInVariableMapOfObjects(variable_map);
    //Set key:
    variable_map->names[*variable_map->size] = malloc(strlen(variable->name));
    if (variable_map->names[*variable_map->size] == NULL) {
        perror("cannot allocate memory for names!");
    }
    variable_map->names[*variable_map->size] = variable->name;
    //Set value:
    variable_map->variables[*variable_map->size] = variable;
    *variable_map->size = *variable_map->size + 1;
}

aio_variable *get_aio_variable_in_map_by_name(aio_variable_map *variable_map, char *name) {
    for (int i = 0; i < strlen(name); ++i) {
        if (strcmp(variable_map->names[i], name) == 0) {
            return variable_map->variables[i];
        }
    }
    perror("cannot get aio variable in map");
}