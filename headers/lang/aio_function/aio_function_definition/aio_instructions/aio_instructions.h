#ifndef AIO_INSTRUCTIONS_H
#define AIO_INSTRUCTIONS_H

#include "../../../../lib/collections/lists/aio_instruction_list.h"
#include "../../../../lib/collections/maps/aio_variable_definition_map.h"
#include "../../../../lib/collections/lists/string_list.h"
#include "../../aio_variable/aio_variable_definition.h"

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
    struct aio_instruction_holder *parent;
    aio_variable_definition_map *local_variable_definition_map;
    aio_instruction_list *instruction_list;
} aio_instruction_holder;

aio_instruction_holder *dig_aio_instruction_holder(const_string source_code, aio_instruction_holder *parent_holder,
                                                   const int start_position, const int end_position);

/**
 * Instruction.
 **/

typedef struct aio_instruction {

    aio_instruction_holder *holder;

    enum aio_task_type task_type;

    union get {
        struct aio_assign_task *assign_task;
        struct aio_if_task *if_task;
        struct aio_loop_task *loop_task;
        struct aio_procedure_task *procedure_task;
        struct aio_return_task *return_task;
        struct aio_switch_task *switch_task;
    } get;

} aio_instruction;

aio_instruction_holder *new_aio_instruction_holder(aio_instruction_holder *parent_holder);

aio_instruction *new_aio_assign_instruction(aio_instruction_holder *holder, const_string source,
                                            const_string destination);

aio_instruction *new_aio_break_instruction(aio_instruction_holder *holder);

aio_instruction *new_aio_if_instruction(aio_instruction_holder *parent_holder, const_string if_condition,
                                        aio_instruction_holder *true_holder, aio_instruction_holder *false_holder);

aio_instruction *new_aio_switch_instruction(aio_instruction_holder *parent_holder, const_string source,
                                            const_string destination);

aio_instruction *new_aio_loop_instruction(aio_instruction_holder *parent_holder, const_string source,
                                          const_string destination);

aio_instruction *new_aio_procedure_instuction(aio_instruction_holder *parent_holder, const_string source,
                                              const_string destination);

aio_instruction *new_aio_return_instruction(aio_instruction_holder *parent_holder, const_string source,
                                            const_string destination);

/**
 * Implement tasks.
 */

typedef struct aio_assign_task {
    const_string source;
    const_string destination;
} aio_assign_task;

typedef struct aio_if_task {
    string if_condition;
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
    //Often for change pointer:
    aio_assign_task *loop_assign_task;
    aio_instruction_holder *loop_holder;
} aio_loop_task;

typedef struct aio_procedure_task {
    string procedure_expression;
} aio_procedure_task;

typedef struct aio_return_task {
    string_list *return_expressions;
} aio_return_task;

#endif //AIO_INSTRUCTIONS_H