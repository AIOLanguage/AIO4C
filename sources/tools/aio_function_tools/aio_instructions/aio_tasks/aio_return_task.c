#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../../headers/lib/utils/collections/lists/string_list.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_return_task.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"

aio_function_instruction * new_aio_return_instruction(
        aio_function_instruction_holder *holder, const_string_list *return_value_list) {
    aio_function_instruction *instruction = new_aio_function_instruction(holder, AIO_RETURN_TASK);
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