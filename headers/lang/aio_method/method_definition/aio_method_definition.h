#include <malloc.h>
#include "aio_method_size_type.h"
#include "../../../lib/collections/lists/aio_annotation_list.h"
#include "../../../lib/collections/lists/string_list.h"
#include "../../../lib/collections/maps/aio_variable_map.h"

#ifndef AIO_METHOD_DEFINITION_H
#define AIO_METHOD_DEFINITION_H

typedef struct aio_method_definition {
    const_string name;
    aio_variable_map *arg_map;
    string_list *source_code;
    aio_annotation_list *annotation_list;
} aio_method_definition;

aio_method_definition *new_aio_method_definition(const_string name, aio_variable_map *arg_map,
                                                 string_list *source_code);

void delete_aio_method_definition(aio_method_definition *method_definition);

#endif //AIO_METHOD_DEFINITION_H