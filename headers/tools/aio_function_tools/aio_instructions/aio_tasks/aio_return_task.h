#ifndef AIO_RETURN_INSTRUCTION_H
#define AIO_RETURN_INSTRUCTION_H

typedef struct aio_return_task {
    struct string_list *return_values;
} aio_return_task;

struct aio_function_instruction *new_aio_return_instruction(
        struct aio_function_instruction_holder *holder,
        const struct string_list *return_value_list
);

void perform_aio_return_instruction(
        const struct aio_function_instruction *instruction,
        const struct aio_function_control_graph *control_graph
);

#endif //AIO_RETURN_INSTRUCTION_H