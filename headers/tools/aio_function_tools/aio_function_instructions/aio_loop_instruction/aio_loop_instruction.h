#ifndef AIO_LOOP_INSTRUCTION_H
#define AIO_LOOP_INSTRUCTION_H

#include "../../../../lib/utils/string_utils/string_utils.h"
#include "../aio_function_instruction_holder.h"
#include "../aio_function_instruction.h"

typedef struct aio_loop_task {
    string loop_condition;
    aio_function_instruction_holder *init_holder;
    aio_function_instruction_holder *cycle_holder;
} aio_loop_task;


aio_function_instruction *new_aio_loop_instruction(aio_function_instruction_holder *holder,
                                                   string loop_condition,
                                                   aio_function_instruction_holder *init_holder,
                                                   aio_function_instruction_holder *cycle_holder);

#endif //AIO_LOOP_INSTRUCTION_H