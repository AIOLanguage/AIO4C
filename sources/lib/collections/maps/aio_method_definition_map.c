#include <mem.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include "../../../../headers/lib/collections/maps/aio_method_definition_map.h"

//Passed JUnitTests!
void new_aio_method_definition_map(aio_method_definition_map **definitionMap) {
    //Create the same definition map:
    *definitionMap = calloc(1, sizeof(aio_method_definition_map));
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
void updateMemoryInMutableMapOfDefinitions(aio_method_definition_map *definitionMap) {
    if (*definitionMap->size + 1 == *definitionMap->capacity) {
        *definitionMap->capacity = *definitionMap->capacity * 2;
        definitionMap->names = realloc(definitionMap->names, *definitionMap->capacity * sizeof(char));
        definitionMap->definitions = realloc(definitionMap->definitions,
                                             *definitionMap->capacity * sizeof(aio_method_definition));
    }
}

//Passed JUnitTests!
void put_aio_method_definition_in_map(aio_method_definition_map *definition_map, aio_method_definition *method_definition) {
    for (int i = 0; i < *definition_map->size; ++i) {
        if (strcmp(definition_map->names[i], method_definition->name) == 0) {
            perror("AIODuplicate definition error!");
        }
    }
    //Check to update:
    updateMemoryInMutableMapOfDefinitions(definition_map);
    //Set key:
    definition_map->names[*definition_map->size] = malloc(strlen(method_definition->name));
    definition_map->names[*definition_map->size] = method_definition->name;
    //Set value:
    definition_map->definitions[*definition_map->size] = method_definition;
    *definition_map->size = *definition_map->size + 1;
}

//Passed JUnitTests!
aio_method_definition *get_aio_method_definition_in_map_by_name(aio_method_definition_map *definition_map, char *name) {
    for (int i = 0; i < *definition_map->size; ++i) {
        if (strcmp(definition_map->names[i], name) == 0) {
            return definition_map->definitions[i];
        }
    }
    perror("can not get aio method definition in map!!!");
}