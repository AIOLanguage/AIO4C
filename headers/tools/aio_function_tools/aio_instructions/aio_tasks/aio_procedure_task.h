#ifndef AIO_PROCEDURE_INSTRUCTION_H
#define AIO_PROCEDURE_INSTRUCTION_H

typedef struct aio_procedure_task {
    char *procedure;
} aio_procedure_task;

struct aio_function_instruction *new_aio_procedure_instruction(
        struct aio_function_instruction_holder *holder,
        char *procedure
);

void perform_aio_procedure_instruction(
        const struct aio_function_instruction *instruction,
        const struct aio_function_control_graph *control_graph
);

#endif //AIO_PROCEDURE_INSTRUCTION_H