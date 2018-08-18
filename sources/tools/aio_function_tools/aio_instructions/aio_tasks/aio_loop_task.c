#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_loop_task.h"

aio_function_instruction *new_aio_loop_instruction(
        struct aio_function_instruction_holder *holder, string loop_condition,
        struct aio_function_instruction_holder *init_holder, struct aio_function_instruction_holder *cycle_holder) {
    aio_function_instruction *instruction = new_aio_function_instruction(holder, AIO_LOOP_TASK);
    //Init task:
    aio_loop_task *task = new_object(sizeof(aio_loop_task));
    task->loop_condition = loop_condition;
    task->init_holder = init_holder;
    task->cycle_holder = cycle_holder;
    instruction->get.loop_task = task;
    return instruction;
}