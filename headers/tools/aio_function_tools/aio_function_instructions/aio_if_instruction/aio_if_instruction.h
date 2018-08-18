#ifndef AIO_IF_INSTRUCTION_H
#define AIO_IF_INSTRUCTION_H


#include "../../../../lib/utils/string_utils/string_utils.h"
#include "../aio_function_instruction_holder.h"
#include "../aio_function_instruction.h"

typedef struct aio_if_task {
    const_string if_condition;
    aio_function_instruction_holder *true_holder;
    aio_function_instruction_holder *false_holder;
} aio_if_task;


aio_function_instruction *new_aio_if_instruction(aio_function_instruction_holder *holder,
                                                 const_string if_condition,
                                                 aio_function_instruction_holder *true_holder,
                                                 aio_function_instruction_holder *false_holder);

#endif //AIO_IF_INSTRUCTION_H
