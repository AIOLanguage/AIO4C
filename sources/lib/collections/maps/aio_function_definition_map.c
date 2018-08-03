#include <mem.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include "../../../../headers/lib/collections/maps/aio_function_definition_map.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"

//Passed JUnitTests!
aio_function_definition_map *new_aio_method_definition_map() {
    //Create the same definition map:
    aio_function_definition_map *definition_map = calloc(1, sizeof(aio_function_definition_map));
    //Create capacity:
    definition_map->capacity = 2;
    //Create size:
    definition_map->size = 0;
    //Create char capacity that equals 2:
    definition_map->names = calloc(2, sizeof(char *));
    //Create definitions that equals 2:
    definition_map->definitions = calloc(2, sizeof(aio_function_definition * ));
    return definition_map;
}

//Passed JUnitTests!
void update_memory_in_method_definition_map(aio_function_definition_map *definition_map) {
    if (definition_map->size + 1 == definition_map->capacity) {
        definition_map->capacity = definition_map->capacity * 2;
        definition_map->names = realloc(definition_map->names, definition_map->capacity * sizeof(char));
        definition_map->definitions = realloc(definition_map->definitions,
                                              definition_map->capacity * sizeof(aio_function_definition));
    }
}

//Passed JUnitTests!
void put_aio_method_definition_in_map(aio_function_definition_map *definition_map,
                                      aio_function_definition *method_definition) {
    for (int i = 0; i < definition_map->size; ++i) {
        if (strcmp(definition_map->names[i], method_definition->name) == 0) {
            perror("duplicate definition of method error!");
            exit(1);
        }
    }
    //Check to update:
    update_memory_in_method_definition_map(definition_map);
    //Set key:
    definition_map->names[definition_map->size] = method_definition->name;
    //Set value:
    definition_map->definitions[definition_map->size] = method_definition;
    definition_map->size++;
}

//Passed JUnitTests!
aio_function_definition *get_aio_method_definition_in_map_by_name(aio_function_definition_map *definition_map,
                                                                  const_string name) {
    for (int i = 0; i < definition_map->size; ++i) {
        if (strcmp(definition_map->names[i], name) == 0) {
            return definition_map->definitions[i];
        }
    }
    throw_error("can not get aio method definition in map!!!");
}