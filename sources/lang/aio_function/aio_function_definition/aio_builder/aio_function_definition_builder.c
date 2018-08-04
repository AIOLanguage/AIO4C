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

aio_annotation_list *dig_annotations(const_string source_code, int *pointer_reference);

string_list *dig_output_types(const_string source_code, int *pointer_reference);

string dig_function_name(const_string source_code, int *pointer_reference);

aio_variable_definition_map *dig_arguments(const_string source_code, int *pointer_reference);

aio_instruction_holder *dig_instructions(const_string source_code, int *pointer_reference);

aio_function_definition *build_function_definition(const_string source_code, int *pointer_reference) {
    aio_annotation_list *annotations = dig_annotations(source_code, pointer_reference);
    string_list *output_types = dig_output_types(source_code, pointer_reference);
    string method_name = dig_function_name(source_code, pointer_reference);
    aio_variable_definition_map *arg_definition_map = dig_arguments(source_code, pointer_reference);
    aio_instruction_holder *instruction_holder = dig_instructions(source_code, pointer_reference);
    return new_aio_method_definition(annotations, output_types, method_name, arg_definition_map, instruction_holder);
}