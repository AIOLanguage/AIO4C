#include "../../../../../headers/tools/aio_function_tools/aio_function_instructions/aio_function_instruction_holder.h"

aio_instruction *new_aio_return_instruction(
        aio_function_instruction_holder *holder, const string_list *return_value_list) {
    aio_instruction *instruction = new_object(sizeof(aio_instruction));
    instruction->holder = holder;
    instruction->task_type = AIO_RETURN_TASK;
    //Init task:
    aio_return_task *task = new_object(sizeof(aio_return_task));
    task->return_values = new_string_list();
    for (int i = 0; i < return_value_list->size; ++i) {
        string new_return_value = new_string(return_value_list->strings[i]);
        add_string_in_list(task->return_values, new_return_value);
    }
    instruction->get.return_task = task;
    return instruction;
}