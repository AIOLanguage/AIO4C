#ifndef AIO_VARIABLE_MAP_H
#define AIO_VARIABLE_MAP_H

#include "../../../lang/methods/variable/aio_variable.h"

typedef struct aio_variable_map {
    int capacity;
    int size;
    char **names;
    aio_variable **variables;
} aio_variable_map;

aio_variable_map new_aio_variable_map();

void put_in_aio_variable_in_map(aio_variable_map *variable_map, aio_variable *variable);

aio_variable *get_aio_variable_in_map_by_name(aio_variable_map *variable_map, char *name);

#endif //AIO_VARIABLE_MAP_H