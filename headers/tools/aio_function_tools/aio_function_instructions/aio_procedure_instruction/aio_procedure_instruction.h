#ifndef AIO_PROCEDURE_INSTRUCTION_H
#define AIO_PROCEDURE_INSTRUCTION_H

#include "../../../../lib/utils/string_utils/string_utils.h"
#include "../aio_function_instruction_holder.h"
#include "../aio_function_instruction.h"

typedef struct aio_procedure_task {
    string expression;
} aio_procedure_task;

aio_function_instruction * new_aio_procedure_instruction(aio_function_instruction_holder *holder, string expression);

#endif //AIO_PROCEDURE_INSTRUCTION_H
