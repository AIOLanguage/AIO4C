#ifndef AIO_VARIABLE_DEFINITION_MAP_H
#define AIO_VARIABLE_DEFINITION_MAP_H

#include "../../utils/string_utils/string_utils.h"
#include "../../../lang/aio_function/variable/aio_variable_definition.h"

typedef struct aio_variable_definition_map {
    int capacity;
    int size;
    string_array names;
    aio_variable_definition **variable_definitions;
} aio_variable_definition_map;

aio_variable_definition_map *new_aio_variable_definition_map();

void put_aio_variable_definition_in_map(aio_variable_definition_map *map, aio_variable_definition *variable_definition);

aio_variable_definition *get_aio_definition_variable_in_map_by_name(
        aio_variable_definition_map *variable_definition_map, const_string name);

void delete_aio_variable_definition_map(aio_variable_definition_map *variable_definition_map);

#endif //AIO_VARIABLE_DEFINITION_MAP_H