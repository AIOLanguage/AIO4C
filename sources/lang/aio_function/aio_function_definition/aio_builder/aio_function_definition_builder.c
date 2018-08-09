#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include <ctype.h>
#include <process.h>
#include "../../../../../headers/lib/collections/lists/string_list.h"
#include "../../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../../headers/lib/utils/operation_utils/operation_utils.h"
#include "../../../../../headers/lang/aio_core/aio_core.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/lib/point_watcher/point_watcher.h"

/**
 * Declare functions.
 */

aio_annotation_list *dig_aio_annotations(const_string source_code, int *pointer_reference);

string_list *dig_output_types(const_string source_code, int *pointer_reference);

string dig_function_name(const_string source_code, int *pointer_reference);

aio_variable_definition_map *dig_arguments(const_string source_code, int *pointer_reference);

void dig_block_body(const_string source_code, int *start_index, int *end_index);

aio_instruction_holder *dig_aio_root_instruction_holder(const_string source_code, int *start_index_ref);

/**
 * Function definition builder.
 */

aio_function_definition *build_aio_function_definition(const_string source_code, int *start_index_ref) {
    aio_annotation_list *annotations = dig_aio_annotations(source_code, start_index_ref);
    string_list *output_types = dig_output_types(source_code, start_index_ref);
    string method_name = dig_function_name(source_code, start_index_ref);
    aio_variable_definition_map *arg_definition_map = dig_arguments(source_code, start_index_ref);
    aio_instruction_holder *holder = dig_aio_root_instruction_holder(source_code, start_index_ref);
    return new_aio_method_definition(annotations, output_types, method_name, arg_definition_map, holder);
}

aio_instruction_holder *dig_aio_root_instruction_holder(const_string source_code, int *start_index_ref) {
    //Dig instruction holder:
    aio_instruction_holder *parent_holder = NULL;
    //Pre start with previous start index:
    int start_index = *start_index_ref;
    int end_index = 0;
    //Init block bounds: start & end indices:
    dig_block_body(source_code, &start_index, &end_index);
    //Change global pointer:
    *start_index_ref = end_index + 1; //Jump over "}":
    aio_instruction_holder *holder = dig_aio_instruction_holder(source_code, parent_holder, start_index, end_index);
    return holder;
}