#ifndef AIO_AIO_ASSIGN_INSTRUCTION_H
#define AIO_AIO_ASSIGN_INSTRUCTION_H

#include "../../../../lib/utils/string_utils/string_utils.h"
#include "../aio_function_instruction.h"

typedef struct aio_assign_task {
    const_string value;
    const_string variable_name;
} aio_assign_task;

aio_function_instruction * new_aio_assign_instruction(aio_function_instruction_holder *holder, const_string source,
                                                      const_string destination);

#endif //AIO_AIO_ASSIGN_INSTRUCTION_H