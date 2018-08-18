#include "../../../../../headers/tools/aio_function_tools/aio_function_instructions/aio_function_instruction.h"

aio_function_instruction * new_aio_if_instruction(
        struct aio_function_instruction_holder *holder, const_string if_condition,
        struct aio_function_instruction_holder *true_holder, struct aio_function_instruction_holder *false_holder) {
    aio_instruction *instruction = new_object(sizeof(aio_instruction));
    instruction->holder = holder;
    instruction->task_type = AIO_IF_TASK;
    //Init task:
    aio_if_task *task = new_object(sizeof(aio_if_task));
    task->if_condition = if_condition;
    task->true_holder = true_holder;
    task->false_holder = false_holder;
    instruction->get.if_task = task;
    return instruction;
}