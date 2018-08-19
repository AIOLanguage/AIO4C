#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include <ctype.h>
#include <process.h>
#include "../../../../headers/lang/aio_function/aio_function_definition/aio_function_definition.h"
#include "../../../../headers/tools/aio_function_tools/aio_definition_rippers/aio_function_definition_rippers.h"

/**
 * Function definition builder.
 */

const_aio_function_definition *build_aio_function_definition(const_string source_code, int *start_index_ref) {
    const_aio_annotation_list *annotations = dig_aio_annotations(source_code, start_index_ref);
    const_str_hook_list *output_types = dig_output_types(source_code, start_index_ref);
    const_str_hook *function_name = dig_function_name(source_code, start_index_ref);
    aio_variable_definition_list *arg_definition_list = dig_arguments(source_code, start_index_ref);
    //Save number of args:
    const int number_of_args = arg_definition_list->size;
    //Pass list to root holder. It will add definitions in arg_definition_list:
    const_aio_function_instruction_holder *holder = inflate_root_aio_instruction_holder(source_code, start_index_ref,
                                                                                        arg_definition_list);
    return new_aio_function_definition(annotations, output_types, function_name, number_of_args, holder);
}