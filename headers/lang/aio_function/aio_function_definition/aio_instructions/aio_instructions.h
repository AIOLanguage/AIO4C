#ifndef AIO_INSTRUCTIONS_H
#define AIO_INSTRUCTIONS_H

#include "../../../../lib/collections/lists/aio_instruction_list.h"
#include "../../../../lib/collections/maps/aio_variable_definition_map.h"
#include "../../../../lib/collections/lists/string_list.h"
#include "../../aio_variable/aio_variable_definition.h"

/**
 * Declare instruction holder.
 */

typedef struct aio_instruction_holder;

/**
 * Declare tasks.
 */

typedef struct aio_assign_task;

typedef struct aio_if_task;

typedef struct aio_switch_task;

typedef struct aio_loop_task;

typedef struct aio_procedure_task;

typedef struct aio_break_task;

typedef struct aio_return_task;

/**
 * Task type.
 */

enum aio_task_type {
    AIO_TASK_ASSIGN, AIO_TASK_IF, AIO_TASK_SWITCH, AIO_TASK_LOOP, AIO_TASK_PROCEDURE, AIO_TASK_BREAK, AIO_TASK_RETURN
};

/**
 * Implement instruction holder.
 */

typedef struct aio_instruction_holder {
    struct aio_instruction_holder *parent_holder;
    aio_variable_definition_map *local_variable_definition_map;
    aio_instruction_list *instruction_list;
} aio_instruction_holder;

aio_instruction_holder *new_aio_instruction_holder(aio_instruction_holder *parent_holder);

/**
 * Create union task.
 */

typedef union aio_union_task {
    struct aio_assign_task *assign_task;
    struct aio_if_task *if_task;
    struct aio_switch_task *switch_task;
    struct aio_loop_task *loop_task;
    struct aio_procedure_task *procedure_task;
    struct aio_break_task *break_task;
    struct aio_return_task *return_task;
} aio_union_task;

/**
 * Create instruction ("generic task").
 */

typedef struct aio_instruction {
    aio_instruction_holder *parent_holder;
    enum aio_task_type task_type;
    union aio_union_task get;
} aio_instruction;

/**
 * Implement tasks.
 */

typedef struct aio_assign_task {
    const_string source;
    const_string destination;
} aio_assign_task;

aio_instruction *new_aio_assign_instruction(aio_instruction_holder *parent_holder, const_string source,
                                            const_string destination);

typedef struct aio_if_task {
    string if_expression;
    aio_instruction_holder *true_holder;
    aio_instruction_holder *false_holder;
} aio_if_task;

typedef struct aio_switch_task {
    string switch_expression;
    string_list *case_expressions;
    aio_instruction_holder **case_holders;
} aio_switch_task;

typedef struct aio_loop_task {
    aio_variable_definition *pointer_definition;
    //Often for init point_watcher:
    aio_assign_task *start_assign_tash;
    //Loop condition:
    string loop_condition;
    //Often for change counter:
    aio_assign_task *loop_assign_task;
    aio_instruction_holder *loop_holder;
} aio_loop_task;

typedef struct aio_procedure_task {
    string procedure_expression;
} aio_procedure_task;

typedef struct aio_return_task {
    string_list *return_expressions;
} aio_return_task;

typedef struct aio_break_task {
} aio_break_task;

#endif //AIO_INSTRUCTIONS_H