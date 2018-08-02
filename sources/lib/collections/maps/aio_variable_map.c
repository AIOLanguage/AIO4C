#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/collections/maps/aio_variable_map.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"

aio_variable_map *new_aio_variable_map() {
    aio_variable_map *variable_map = calloc(1, sizeof(aio_variable_map));
    variable_map->capacity = 2;
    variable_map->size = 0;
    variable_map->names = calloc(2, sizeof(string));
    variable_map->variables = calloc(2, sizeof(aio_variable *));
    return variable_map;
}

//Passed JUnitTests!
void update_memory_in_variable_map(aio_variable_map *variable_map) {
    if (variable_map->size + 1 == variable_map->capacity) {
        variable_map->capacity = variable_map->capacity * 2;
        variable_map->names = realloc(variable_map->names, variable_map->capacity * sizeof(char *));
        variable_map->variables = realloc(variable_map->variables, variable_map->capacity * sizeof(aio_variable *));
    }
}

void put_aio_variable_in_map(aio_variable_map *variable_map, aio_variable *variable) {
    for (int i = 0; i < variable_map->size; ++i) {
        if (strcmp(variable_map->names[i], variable->variable_definition->name) == 0) {
            perror("Cannot put aio_context in definition map");
        }
    }
    //Check to update:
    update_memory_in_variable_map(variable_map);
    //Set key:
    variable_map->names[variable_map->size] = malloc(strlen(variable->variable_definition->name));
    if (variable_map->names[variable_map->size] == NULL) {
        perror("cannot allocate memory for names!");
    }
    variable_map->names[variable_map->size] = variable->variable_definition->name;
    //Set value:
    variable_map->variables[variable_map->size] = variable;
    variable_map->size++;
}

aio_variable *get_aio_variable_in_map_by_name(aio_variable_map *variable_map, const_string name) {
    for (int i = 0; i < strlen(name); ++i) {
        if (strcmp(variable_map->names[i], name) == 0) {
            return variable_map->variables[i];
        }
    }
    throw_error("cannot get aio variable in map");
}