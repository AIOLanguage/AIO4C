#ifndef AIO_FUNCTION_RIPPERS_H
#define AIO_FUNCTION_RIPPERS_H

#include "../../../lib/collections/lists/aio_annotation_list.h"
#include "../../../lib/collections/lists/string_list.h"
#include "../../../lib/collections/maps/aio_variable_definition_map.h"
#include "../../../lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"

aio_annotation_list *dig_aio_annotations(const_string source_code, int *pointer_reference);

string_list *dig_output_types(const_string source_code, int *pointer_reference);

string dig_function_name(const_string source_code, int *pointer_reference);

aio_variable_definition_map *dig_arguments(const_string source_code, int *pointer_reference);

aio_instruction_holder *dig_aio_root_instruction_holder(const_string source_code, int *start_code_pointer_ref,
                                                        aio_variable_definition_map *arg_definition_map);

#endif //AIO_FUNCTION_RIPPERS_H