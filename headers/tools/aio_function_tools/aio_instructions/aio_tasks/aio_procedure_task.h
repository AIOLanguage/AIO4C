#ifndef AIO_PROCEDURE_INSTRUCTION_H
#define AIO_PROCEDURE_INSTRUCTION_H

#include "../../../../lib/utils/string_utils/string_utils.h"
#include "../aio_function_instruction_holder.h"
#include "../aio_function_instruction.h"

typedef struct aio_procedure_task {
    string procedure;
} aio_procedure_task;

aio_function_instruction * new_aio_procedure_instruction(aio_function_instruction_holder *holder, string procedure);

void perform_aio_procedure_instruction(const_aio_function_instruction *instruction,
                                       const_aio_function_control_graph *control_graph);

#endif //AIO_PROCEDURE_INSTRUCTION_H
