#ifndef AIO_FUNCTION_INSTRUCTION_H
#define AIO_FUNCTION_INSTRUCTION_H

/**
 * Linking.
 */

#include <tools/aio_function_tools/aio_instructions/aio_function_instruction.h>
#include <tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h>

/**
 * Task type.
 */

typedef enum aio_function_task_type {
    AIO_ASSIGN_TASK,
    AIO_BREAK_TASK,
    AIO_CONTINUE_TASK,
    AIO_IF_TASK,
    AIO_LOOP_TASK,
    AIO_PROCEDURE_TASK,
    AIO_RETURN_TASK,
    AIO_SWITCH_TASK
} aio_function_task_type;

/**
 * Instruction.
 **/

typedef struct aio_function_instruction {

    struct aio_function_instruction_holder *holder;

    enum aio_function_task_type task_type;

    union {
        const struct aio_assign_task *assign_task;
        const struct aio_if_task *if_task;
        const struct aio_loop_task *loop_task;
        const struct aio_procedure_task *procedure_task;
        const struct aio_return_task *return_task;
        const struct aio_switch_task *switch_task;
    } get;

} aio_function_instruction;

struct aio_function_instruction *new_aio_function_instruction(
        struct aio_function_instruction_holder *holder,
        enum aio_function_task_type task_type
);

void perform_aio_instruction(
        const struct aio_function_instruction *instruction,
        const struct aio_function_control_graph *control_graph
);

/**
 * Instruction list.
 */

typedef struct aio_function_instruction_list {
    unsigned capacity;
    unsigned size;
    const struct aio_function_instruction **instructions;
} aio_function_instruction_list;

struct aio_function_instruction_list *new_aio_function_instruction_list();

void add_aio_instruction_in_list(
        struct aio_function_instruction_list *list,
        const struct aio_function_instruction *instruction
);

void free_aio_instruction_list(struct aio_function_instruction_list *list);

#endif //AIO_FUNCTION_INSTRUCTION_H