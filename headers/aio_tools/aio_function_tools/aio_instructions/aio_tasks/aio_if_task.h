#ifndef AIO_IF_INSTRUCTION_H
#define AIO_IF_INSTRUCTION_H

typedef struct aio_if_task {
    const char *if_condition;
    struct aio_function_instruction_holder *true_holder;
    struct aio_function_instruction_holder *false_holder;
} aio_if_task;

struct aio_function_instruction *new_aio_if_instruction(
        struct aio_function_instruction_holder *holder,
        const char *if_condition,
        struct aio_function_instruction_holder *true_holder,
        struct aio_function_instruction_holder *false_holder
);

void perform_aio_if_instruction(
        const struct aio_function_instruction *instruction,
        const struct aio_function_control_graph *control_graph
);

#endif //AIO_IF_INSTRUCTION_H