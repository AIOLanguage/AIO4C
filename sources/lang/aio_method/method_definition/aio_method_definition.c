#include <stddef.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lang/aio_method/method_definition/aio_method_definition.h"

aio_method_definition *
new_aio_method_definition(const_string name, aio_variable_definition_map *arg_definition_map, string_list *source_code,
                          string_list *return_type_list) {
    aio_method_definition *method_definition = calloc(1, sizeof(aio_method_definition));
    method_definition->name = name;
    method_definition->source_code = source_code;
    method_definition->input_argument_definition_map = arg_definition_map;
    return method_definition;
}