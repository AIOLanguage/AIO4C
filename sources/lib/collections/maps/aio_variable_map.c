#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/collections/maps/aio_variable_map.h"

aio_variable_map *new_aio_variable_map() {
    aio_variable_map *variable_map = calloc(1, sizeof(aio_variable_map));
    //create capacity:
    variable_map->capacity = 2;
    //create size:
    variable_map->size = 0;
    //create char capacity that equals 2:
    variable_map->names = calloc(2, sizeof(string));
    //create definitions that equals 2:
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
        if (strcmp(variable_map->names[i], variable->name) == 0) {
            perror("Cannot put aio_file in definition map");
        }
    }
    //Check to update:
    update_memory_in_variable_map(variable_map);
    //Set key:
    variable_map->names[variable_map->size] = malloc(strlen(variable->name));
    if (variable_map->names[variable_map->size] == NULL) {
        perror("cannot allocate memory for names!");
    }
    variable_map->names[variable_map->size] = variable->name;
    //Set value:
    variable_map->variables[variable_map->size] = variable;
    variable_map->size++;
}

aio_variable *get_aio_variable_in_map_by_name(aio_variable_map *variable_map, char *name) {
    for (int i = 0; i < strlen(name); ++i) {
        if (strcmp(variable_map->names[i], name) == 0) {
            return variable_map->variables[i];
        }
    }
    perror("cannot get aio variable in map");
}