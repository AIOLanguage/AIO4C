#ifndef AIO_AIO_INSTRUCTIONS_H
#define AIO_AIO_INSTRUCTIONS_H

#include "aio_instruction_entry.h"

typedef struct aio_assign_instruction {
    aio_instruction_entry *parent_entry_instruction;
    const_string source_expression_or_variable_name;
    const_string destination_variable_name;
} aio_assign_instruction;

typedef struct aio_if_instruction {
    aio_instruction_entry *parent_entry_instruction;
    const_string expression;
    aio_instruction_holder *true_instruction;
    aio_instruction_holder *false_instruction;
} aio_if_instruction;

typedef struct aio_switch_instruction {
    aio_instruction_entry *parent_entry_instruction;
    string_list *expressions;
    aio_instruction_list *instruction_list;
} aio_switch_instruction;

typedef struct aio_loop_instruction {
    aio_instruction_entry *parent_entry_instruction;
    aio_variable_definition *pointer_variable_definition;
    //Often for init pointer:
    aio_assign_instruction *start_assign_instruction;
    const_string loop_condition;
    //Instructions:
    aio_instruction_list *instruction_list;
    //Often for change counter:
    aio_assign_instruction *loop_assign_instruction;
} aio_loop_instruction;

typedef struct aio_procedure_instruction {
    aio_instruction_entry *parent_entry_instruction;
    const_string expression;
} aio_procedure_instruction;

typedef struct aio_out_instruction {
    aio_instruction_entry *parent_entry_instruction;
    string_list *expressions;
} aio_out_instruction;

typedef struct aio_break_instruction {
    aio_instruction_entry *parent_entry_instruction;
} aio_break_instruction;

#endif //AIO_AIO_INSTRUCTIONS_H