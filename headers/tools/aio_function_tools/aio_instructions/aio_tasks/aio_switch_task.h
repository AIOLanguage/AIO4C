#ifndef AIO_SWITCH_INSTRUCTION_H
#define AIO_SWITCH_INSTRUCTION_H

typedef struct aio_switch_task {
    const char *switch_value;
    struct string_list *case_keys;
    struct aio_function_instruction_holder **case_holders;
    struct aio_function_instruction_holder *else_holder;
} aio_switch_task;

struct aio_function_instruction *new_aio_switch_instruction(
        struct aio_function_instruction_holder *holder,
        const char *switch_value,
        struct string_list *case_keys,
        struct aio_function_instruction_holder **case_holders,
        struct aio_function_instruction_holder *else_holder
);

void perform_aio_switch_instruction(
        const struct aio_function_instruction *instruction,
        const struct aio_function_control_graph *control_graph
);

#endif //AIO_SWITCH_INSTRUCTION_H