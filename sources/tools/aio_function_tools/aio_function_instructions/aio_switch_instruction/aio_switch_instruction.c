#include "../../../../../headers/tools/aio_function_tools/aio_function_instructions/aio_function_instruction.h"

aio_function_instruction * new_aio_switch_instruction(
        struct aio_function_instruction_holder *holder, const_string switch_value,
        string_list *case_keys, struct aio_function_instruction_holder **case_holders,
        struct aio_function_instruction_holder *else_holder) {
    aio_instruction *instruction = new_object(sizeof(aio_instruction));
    instruction->holder = holder;
    instruction->task_type = AIO_SWITCH_TASK;
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