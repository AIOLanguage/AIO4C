#ifndef AIO_BREAK_INSTRUCTION_H
#define AIO_BREAK_INSTRUCTION_H

#include "../aio_function_instruction_holder.h"
#include "../aio_function_instruction.h"

aio_function_instruction *new_aio_break_instruction(aio_function_instruction_holder *holder);

static const_aio_function_instruction_holder *get_aio_loop_holder_in_tree() {

}

void perform_aio_break_instruction(const_aio_function_instruction *instruction,
                                   const_aio_function_control_graph *control_graph) {
    const_aio_function_instruction_holder *instruction_holder = instruction->holder;

}

#endif //AIO_BREAK_INSTRUCTION_H
