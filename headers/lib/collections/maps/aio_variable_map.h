#ifndef AIO_VARIABLE_MAP_H
#define AIO_VARIABLE_MAP_H

#include "../../utils/string_utils/string_utils.h"
#include "../../../lang/aio_function/variable/aio_variable.h"

typedef struct aio_variable_map {
    int capacity;
    int size;
    string_array names;
    aio_variable **variables;
} aio_variable_map;

aio_variable_map *new_aio_variable_map();

void put_aio_variable_in_map(aio_variable_map *variable_map, aio_variable *variable);

aio_variable *get_aio_variable_in_map_by_name(aio_variable_map *variable_map, const_string name);

void delete_aio_variable_map(aio_variable_map *variable_map);

#endif //AIO_VARIABLE_MAP_H