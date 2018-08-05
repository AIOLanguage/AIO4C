#include <malloc.h>
#include <mem.h>
#include "../../../../headers/lib/collections/maps/aio_variable_definition_map.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"

aio_variable_definition_map *new_aio_variable_definition_map() {
    aio_variable_definition_map *variable_map = calloc(1, sizeof(aio_variable_definition_map));
    variable_map->capacity = 2;
    variable_map->size = 0;
    variable_map->variable_definitions = calloc(2, sizeof(aio_variable_definition *));
    return variable_map;
}

void update_memory_in_variable_definition_map(aio_variable_definition_map *map) {
    if (map->size + 1 == map->capacity) {
        map->capacity = map->capacity * 2;
        map->variable_definitions = realloc(map->variable_definitions,
                                            map->capacity * sizeof(aio_variable_definition *));
    }
}

void put_aio_variable_definition_in_map(aio_variable_definition_map *map, aio_variable_definition *definition) {
    for (int i = 0; i < map->size; ++i) {
        if (strcmp(map->variable_definitions[i]->name, definition->name) == 0) {
            throw_error("Cannot put variable definition in map!");
        }
    }
    //Check to update:
    update_memory_in_variable_definition_map(map);
    //Set aio_value:
    map->variable_definitions[map->size] = definition;
    map->size++;
}

aio_variable_definition *get_aio_variable_definition_in_map_by_name(aio_variable_definition_map *map
        , const_string name) {
    for (int i = 0; i < map->size; ++i) {
        aio_variable_definition *definition = map->variable_definitions[i];
        if (strcmp(definition->name, name) == 0) {
            return definition;
        }
    }
    throw_error("Cannot get aio aio variable definition in map");
}