#ifndef AIO_INSTRUCTION_HOLDER_H
#define AIO_INSTRUCTION_HOLDER_H

typedef struct aio_function_instruction_holder {
    struct aio_function_instruction_holder *parent;
    struct aio_variable_definition_list *variable_definition_list;
    struct aio_function_instruction_list *instruction_list;
} aio_function_instruction_holder;

struct aio_function_instruction_holder *new_aio_function_instruction_holder(
        struct aio_function_instruction_holder *parent_holder
);

struct aio_function_instruction_holder *inflate_root_aio_instruction_holder(
        char *source_code,
        int *start_code_pointer_ref,
        struct aio_variable_definition_list *arg_definitions
);

struct aio_function_instruction_holder *inflate_local_aio_instruction_holder(
        char *source_code,
        struct aio_function_instruction_holder *parent_holder,
        int start_index,
        int end_index
);

void free_aio_function_instruction_holder(struct aio_function_instruction_holder *holder);

#endif //AIO_INSTRUCTION_HOLDER_H