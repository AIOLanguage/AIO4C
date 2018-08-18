#ifndef AIO_FUNCTION_INSTRUCTION_H
#define AIO_FUNCTION_INSTRUCTION_H

#include "aio_function_instruction_holder.h"

/**
 * Task type.
 */

typedef enum aio_function_task_type {
    AIO_ASSIGN_TASK, AIO_BREAK_TASK, AIO_IF_TASK, AIO_LOOP_TASK, AIO_PROCEDURE_TASK, AIO_RETURN_TASK, AIO_SWITCH_TASK
} aio_function_task_type;

/**
 * Instruction.
 **/

typedef struct aio_function_instruction {

    struct aio_function_instruction_holder *holder;

    aio_function_task_type task_type;

    union get {
        struct aio_assign_task *assign_task;
        struct aio_if_task *if_task;
        struct aio_loop_task *loop_task;
        struct aio_procedure_task *procedure_task;
        struct aio_return_task *return_task;
        struct aio_switch_task *switch_task;
    } get;

} aio_function_instruction;

typedef const aio_function_instruction const_aio_function_instruction;

aio_function_instruction *new_aio_function_instruction(aio_function_instruction_holder *holder,
                                                       aio_function_task_type task_type);

/**
 * Instruction list.
 */

typedef struct aio_function_instruction_list {
    int capacity;
    int size;
    const aio_function_instruction **instructions;
} aio_function_instruction_list;

typedef const aio_function_instruction_list const_aio_function_instruction_list;

aio_function_instruction_list *new_aio_function_instruction_list();

void add_aio_instruction_in_list(aio_function_instruction_list *list, const_aio_function_instruction *instruction);

void free_aio_instruction_list(aio_function_instruction_list *list);

#endif //AIO_FUNCTION_INSTRUCTION_H