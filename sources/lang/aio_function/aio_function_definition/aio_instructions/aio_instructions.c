#include <malloc.h>
#include "../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"

aio_instruction_holder *new_aio_instruction_holder(aio_instruction_holder *parent_holder) {
    aio_instruction_holder* holder = calloc(1, sizeof(aio_instruction_holder));
    holder->parent_holder = parent_holder;
    holder->local_variable_definition_map = new_aio_variable_definition_map();
    holder->instruction_entry_list = new_aio_instruction_list();
    return holder;
}