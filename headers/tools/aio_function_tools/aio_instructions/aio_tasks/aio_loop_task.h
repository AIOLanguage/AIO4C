#ifndef AIO_LOOP_INSTRUCTION_H
#define AIO_LOOP_INSTRUCTION_H

typedef struct aio_loop_task {
    char *loop_condition;
    struct aio_function_instruction_holder *init_holder;
    struct aio_function_instruction_holder *cycle_holder;
} aio_loop_task;

struct aio_function_instruction *new_aio_loop_instruction(
        struct aio_function_instruction_holder *holder,
        char *loop_condition,
        struct aio_function_instruction_holder *init_holder,
        struct aio_function_instruction_holder *cycle_holder
);

void perform_aio_loop_instruction(
        const struct aio_function_instruction *instruction,
        const struct aio_function_control_graph *control_graph
);

#endif //AIO_LOOP_INSTRUCTION_H