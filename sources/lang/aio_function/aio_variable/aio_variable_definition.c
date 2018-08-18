#include <malloc.h>
#include "../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../headers/lang/aio_function/aio_variable/aio_variable_definition.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"

aio_variable_definition *new_aio_variable_definition(string name, string type,
                                                     const_boolean is_mutable_by_value) {
    aio_variable_definition *definition = new_object(sizeof(aio_variable_definition));
    definition->name = name;
    definition->type = type;
    definition->is_mutable_by_value = is_mutable_by_value;
    return definition;
}

void free_aio_variable_definition(aio_variable_definition *definition) {
    free(definition);
}

const_aio_variable_definition *get_variable_definition_in_function_tree(const_str_hook variable_name,
                                                                        const_aio_function_instruction_holder
                                                                        *child_holder) {
    const_aio_variable_definition_list *list = child_holder->variable_definition_map;
    const_aio_variable_definition *variable_definition = get_aio_variable_definition_in_map_by_name(list, variable_name);
    if (variable_definition == NULL) {
        aio_instruction_holder *parent_holder = child_holder->parent;
        if (parent_holder != NULL) {
            return get_variable_definition_in_function_tree(variable_name, parent_holder);
        } else {
            return NULL;
        }
    }
}














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
    //Check from update:
    update_memory_in_variable_definition_map(map);
    //Set aio_valu:
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
    return NULL;
}