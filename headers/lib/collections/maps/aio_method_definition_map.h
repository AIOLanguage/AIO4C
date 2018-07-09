#ifndef AIO_METHOD_DEFINITION_MAP_H
#define AIO_METHOD_DEFINITION_MAP_H

#include "../../../lang/aio_method/method_definition/aio_method_definition.h"

typedef struct aio_method_definition_map {
    int capacity;
    int size;
    string_array names;
    aio_method_definition **definitions;
} aio_method_definition_map;

aio_method_definition_map *new_aio_method_definition_map();

void put_aio_method_definition_in_map(aio_method_definition_map *definition_map,
                                      aio_method_definition *method_definition);

aio_method_definition *get_aio_method_definition_in_map_by_name(aio_method_definition_map *definition_map,
                                                                const_string name);

void delete_aio_method_definition_map(aio_method_definition_map *method_definition_map);

#endif //AIO_METHOD_DEFINITION_MAP_H