#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include <ctype.h>
#include <process.h>
#include "../../../../headers/lib/collections/lists/string_list.h"
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lib/utils/operation_utils/operation_utils.h"
#include "../../../../headers/lang/aio_core/aio_core.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"


aio_annotation_list *delve_annotations(const_string source_code, int *pointer_reference) {
    return new_annotation_list();
}

string_list *delve_output_types(const_string source_code, int *pointer_reference) {
    const size_t source_code_length = strlen(source_code);
    for (int i = 0; i < source_code_length; ++i) {


    }
    //return ;
}

const_string delve_function_name(const_string source_code, int *poiner_reference) {
    return NULL;
}

aio_variable_definition_map *delve_arguments(const_string source_code, int *pointer_reference) {
    aio_variable_definition_map *result;
    return result;
}

aio_instruction_holder *delve_instructions(const_string source_code, int *pointer_reference) {
    return NULL;
}

aio_function_definition *delve_method_definition(const_string source_code, int *pointer_reference) {
    aio_annotation_list *annotations = delve_annotations(source_code, pointer_reference);
    string_list *output_types = delve_output_types(source_code, pointer_reference);
    const_string method_name = delve_function_name(source_code, pointer_reference);
    aio_variable_definition_map *arg_definition_map = delve_arguments(source_code, pointer_reference);
    aio_instruction_holder *instruction_holder = delve_instructions(source_code, pointer_reference);
    return new_aio_method_definition(annotations, output_types, method_name, arg_definition_map, instruction_holder);
}