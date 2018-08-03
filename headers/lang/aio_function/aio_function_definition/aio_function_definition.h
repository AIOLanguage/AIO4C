#include <malloc.h>
#include "../../../lib/collections/lists/aio_annotation_list.h"
#include "../../../lib/collections/lists/string_list.h"
#include "../../../lib/collections/maps/aio_variable_map.h"
#include "../../../lib/collections/maps/aio_variable_definition_map.h"
#include "aio_instructions/aio_instructions.h"

#ifndef AIO_METHOD_DEFINITION_H
#define AIO_METHOD_DEFINITION_H

typedef struct aio_function_definition {
    aio_annotation_list *annotation_list;
    string_list *output_type_list;
    const_string name;
    aio_variable_definition_map *arg_definition_map;
    aio_instruction_holder *instruction_holder;
} aio_function_definition;

aio_function_definition *new_aio_method_definition(aio_annotation_list *annotations, string_list *output_type_list,
                                                   const_string name, aio_variable_definition_map *arg_definition_map,
                                                   aio_instruction_holder *instruction_holder);

void delete_aio_method_definition(aio_function_definition *method_definition);

#endif //AIO_METHOD_DEFINITION_H