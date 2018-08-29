#ifndef AIO_AIO_ASSIGN_INSTRUCTION_H
#define AIO_AIO_ASSIGN_INSTRUCTION_H

typedef struct aio_assign_task {
    const char *value;
    const struct str_hook *variable_name;
} aio_assign_task;

struct aio_function_instruction *new_aio_assign_instruction(
        struct aio_function_instruction_holder *holder,
        const char *value,
        const struct str_hook *variable_name
);

void perform_aio_assign_instruction(
        const struct aio_function_instruction *instruction,
        const struct aio_function_control_graph *control_graph
);

#endif //AIO_AIO_ASSIGN_INSTRUCTION_H