#include "../../../../../headers/tools/aio_function_tools/aio_function_instructions/aio_function_instruction_holder.h"

aio_instruction *new_aio_procedure_instruction(
        aio_function_instruction_holder *holder, string expression) {
    aio_instruction *instruction = new_object(sizeof(aio_instruction));
    instruction->holder = holder;
    instruction->task_type = AIO_PROCEDURE_TASK;
    //Init task:
    aio_procedure_task *task = new_object(sizeof(aio_procedure_task));
    task->expression = expression;
    instruction->get.procedure_task = task;
    return instruction;
}