#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../../headers/lib/utils/collections/lists/string_list.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_switch_task.h"

aio_function_instruction * new_aio_switch_instruction(
        struct aio_function_instruction_holder *holder, const_string switch_value,
        string_list *case_keys, struct aio_function_instruction_holder **case_holders,
        struct aio_function_instruction_holder *else_holder) {
    aio_function_instruction *instruction = new_aio_function_instruction(holder, AIO_SWITCH_TASK);
    //Init task:
    aio_switch_task *task = new_object(sizeof(aio_switch_task));
    task->switch_value = switch_value;
    task->case_keys = case_keys;
    task->case_holders = case_holders;
    task->else_holder = else_holder;
    task->is_not_equals_any_cases = TRUE;
    instruction->get.switch_task = task;
    return instruction;
}