#ifndef AIO_FUNCTION_DEFINITION_SPIDER_H
#define AIO_FUNCTION_DEFINITION_SPIDER_H

#include "../aio_function_instructions/aio_function_instruction_holder.h"
#include "../../../lang/aio_annotation/aio_annotation.h"
#include "../../../lib/utils/collections/lists/string_list.h"
#include "../../../lang/aio_function/aio_variable/aio_variable_definition/aio_variable_definition.h"

const_aio_annotation_list * dig_aio_annotations(const_string source_code, int *pointer_reference);

const_str_hook_list * dig_output_types(const_string source_code, int *pointer_reference);

const_str_hook * dig_function_name(const_string source_code, int *pointer_reference);

aio_variable_definition_list *dig_arguments(const_string source_code, int *pointer_reference);

void dig_aio_instructions_for(aio_function_instruction_holder *current_holder, const_string source_code,
                              const int start_index, const int end_index);

#endif //AIO_FUNCTION_DEFINITION_SPIDER_H