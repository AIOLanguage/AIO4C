#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_assign_task.h"

aio_function_instruction *new_aio_assign_instruction(
        aio_function_instruction_holder *holder, const_string source,
        const_string destination) {
    aio_function_instruction *instruction = new_aio_function_instruction(holder, AIO_ASSIGN_TASK);
    //Init task:
    aio_assign_task *task = new_object(sizeof(aio_assign_task));
    task->value = new_string(source);
    task->variable_name = new_string(destination);
    instruction->get.assign_task = task;
    return instruction;
}