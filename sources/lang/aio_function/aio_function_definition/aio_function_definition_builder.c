#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include <ctype.h>
#include <process.h>
#include "../../../../headers/lang/aio_function/aio_function_definition/aio_function_definition.h"
#include "../../../../headers/tools/aio_parsers/aio_function_rippers/aio_function_rippers.h"

/**
 * Function definition builder.
 */

aio_function_definition *build_aio_function_definition(const_string source_code, int *start_index_ref) {
    aio_annotation_list *annotations = dig_aio_annotations(source_code, start_index_ref);
    string_list *output_types = dig_output_types(source_code, start_index_ref);
    string method_name = dig_function_name(source_code, start_index_ref);
    aio_variable_definition_map *arg_definition_map = dig_arguments(source_code, start_index_ref);
    aio_instruction_holder *holder = dig_aio_root_instruction_holder(source_code, start_index_ref, arg_definition_map);
    return new_aio_method_definition(annotations, output_types, method_name, arg_definition_map, holder);
}