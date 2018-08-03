#ifndef AIO_AIO_INSTRUCTIONS_H
#define AIO_AIO_INSTRUCTIONS_H

#include "../../../../lib/collections/lists/aio_instruction_list.h"
#include "../../../../lib/collections/maps/aio_variable_definition_map.h"
#include "../../../../lib/collections/lists/string_list.h"

typedef struct aio_assign_instruction;

typedef struct aio_if_instruction;

typedef struct aio_switch_instruction;

typedef struct aio_loop_instruction;

typedef struct aio_procedure_instruction;

typedef struct aio_break_instruction;

typedef struct aio_out_instruction;

enum aio_instruction_type {
    ASSIGN, IF, SWITCH, LOOP, PROCEDURE, BREAK, OUT
};

typedef union aio_instruction_entry {
    enum aio_instruction_type instruction_type;
    struct aio_assign_instruction *assign_instruction;
    struct aio_if_instruction *if_instruction;
    struct aio_switch_instruction *switch_instruction;
    struct aio_loop_instruction *loop_instruction;
    struct aio_procedure_instruction *procedure_instruction;
    struct aio_break_instruction *break_instruction;
    struct aio_out_instruction *out_instruction;
} aio_instruction_entry;

typedef struct aio_instruction_holder {
    aio_instruction_entry *parent_entry_instruction;
    //Keep string expression, key is index:
    aio_variable_definition_map *local_variable_definition_map;
    aio_instruction_list *instructions;
} aio_instruction_holder;


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