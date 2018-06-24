#ifndef AIO_METHOD_DEFINITION_MAP_H
#define AIO_METHOD_DEFINITION_MAP_H


#include "../../../lang/methods/method_definition/aio_method_definition.h"

typedef struct aio_method_definition_map {
    int capacity;
    int size;
    char **names;
    aio_method_definition **definitions;
} aio_method_definition_map;

aio_method_definition_map *new_aio_method_definition_map();

void put_aio_method_definition_in_map(aio_method_definition_map *definition_map,
                                      aio_method_definition *method_definition);

aio_method_definition *get_aio_method_definition_in_map_by_name(aio_method_definition_map *definition_map, char *name);

#endif //AIO_METHOD_DEFINITION_MAP_H