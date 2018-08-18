#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_if_task.h"

aio_function_instruction * new_aio_if_instruction(
        struct aio_function_instruction_holder *holder, const_string if_condition,
        struct aio_function_instruction_holder *true_holder, struct aio_function_instruction_holder *false_holder) {
    aio_function_instruction *instruction = new_aio_function_instruction(holder, AIO_IF_TASK);
    //Init task:
    aio_if_task *task = new_object(sizeof(aio_if_task));
    task->if_condition = if_condition;
    task->true_holder = true_holder;
    task->false_holder = false_holder;
    instruction->get.if_task = task;
    return instruction;
}