#ifndef AIO_BREAK_INSTRUCTION_H
#define AIO_BREAK_INSTRUCTION_H

#include "../aio_function_instruction_holder.h"
#include "../aio_function_instruction.h"

aio_function_instruction *new_aio_break_instruction(aio_function_instruction_holder *holder);

aio_function_instruction *new_aio_continue_instruction(aio_function_instruction_holder *holder);

void perform_aio_break_instruction(const_aio_function_control_graph *control_graph);

void perform_aio_continue_instruction(const_aio_function_control_graph *control_graph);

#endif //AIO_BREAK_INSTRUCTION_H