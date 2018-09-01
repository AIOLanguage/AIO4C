#ifndef AIO_BREAK_INSTRUCTION_H
#define AIO_BREAK_INSTRUCTION_H

struct aio_function_instruction *new_aio_break_instruction(struct aio_function_instruction_holder *holder);

struct aio_function_instruction *new_aio_continue_instruction(struct aio_function_instruction_holder *holder);

void perform_aio_break_instruction(const struct aio_function_control_graph *control_graph);

void perform_aio_continue_instruction(const struct aio_function_control_graph *control_graph);

#endif //AIO_BREAK_INSTRUCTION_H