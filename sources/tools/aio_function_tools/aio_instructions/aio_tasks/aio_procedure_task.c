#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_procedure_task.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"

aio_function_instruction * new_aio_procedure_instruction(
        aio_function_instruction_holder *holder, string expression) {
    aio_function_instruction *instruction = new_aio_function_instruction(holder, AIO_PROCEDURE_TASK);
    //Init task:
    aio_procedure_task *task = new_object(sizeof(aio_procedure_task));
    task->expression = expression;
    instruction->get.procedure_task = task;
    return instruction;
}