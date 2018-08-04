#include <stddef.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/collections/lists/aio_annotation_list.h"
#include "../../../../headers/lang/aio_function/aio_function_definition/aio_function_definition.h"

aio_function_definition *
new_aio_method_definition(aio_annotation_list *annotations, string_list *output_type_list, string name,
                          aio_variable_definition_map *arg_definition_map, aio_instruction_holder *instruction_holder) {
    aio_function_definition *method_definition = calloc(1, sizeof(aio_function_definition));
    method_definition->annotation_list = annotations;
    method_definition->output_type_list = output_type_list;
    method_definition->name = name;
    method_definition->arg_definition_map = arg_definition_map;
    method_definition->instruction_holder = instruction_holder;
    return method_definition;
}