#ifndef AIO_INSTRUCTION_HOLDER_H
#define AIO_INSTRUCTION_HOLDER_H

#include "../../../lang/aio_function/aio_variable/aio_variable_definition.h"
#include "aio_function_instruction.h"

typedef struct aio_function_instruction_holder {
    struct aio_function_instruction_holder *parent;
    aio_variable_definition_list *variable_definition_map;
    aio_function_instruction_list *instruction_list;
} aio_function_instruction_holder;

typedef const aio_function_instruction_holder const_aio_function_instruction_holder;

aio_function_instruction_holder *new_aio_instruction_holder(aio_function_instruction_holder *parent_holder);

aio_function_instruction_holder *inflate_aio_root_instruction_holder(const_string source_code,
                                                                     int *start_code_pointer_ref,
                                                                     aio_variable_definition_list *arg_definition_map);

aio_function_instruction_holder *inflate_local_aio_instruction_holder(const_string source_code,
                                                                      aio_function_instruction_holder *parent_holder,
                                                                      const int start_index, const int end_index);

#endif //AIO_INSTRUCTION_HOLDER_H