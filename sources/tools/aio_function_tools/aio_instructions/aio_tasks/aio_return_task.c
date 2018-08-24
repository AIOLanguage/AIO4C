#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../../headers/lib/utils/collections/lists/string_list.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_return_task.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"
#include "../../../../../headers/lib/utils/log_utils/log_utils.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"

#define AIO_RETURN_TASK_TAG "AIO_RETURN_TASK"

#define AIO_RETURN_TASK_DEBUG

#ifdef AIO_RETURN_TASK_DEBUG
#endif

aio_function_instruction *new_aio_return_instruction(
        aio_function_instruction_holder *holder, const_string_list *return_value_list)
{
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

void perform_aio_return_instruction(const_aio_function_instruction *instruction,
                                    const_aio_function_control_graph *control_graph)
{
    //Extract control graph:
    const_aio_context *context_ref = control_graph->context_ref;
    aio_bundle *bundle = control_graph->bundle_ref;
    aio_value_list *output_value_list = bundle->output_values;
    //Extract task:
    const aio_return_task *task = instruction->get.return_task;
    const_string_list *return_value_string_list = task->return_values;
    const_string_array return_value_string_array = return_value_string_list->strings;
    const size_t return_value_list_size = return_value_string_list->size;
    //Fill bundle:
#ifdef AIO_RETURN_TASK_DEBUG
    log_info_int(AIO_RETURN_TASK_TAG, "SIZE:", return_value_list_size);
#endif
    for (int i = 0; i < return_value_list_size; ++i) {
        const_string return_value_string = return_value_string_array[i];
#ifdef AIO_RETURN_TASK_DEBUG
        log_info_string(AIO_RETURN_TASK_TAG, "Return expression string:", return_value_string);
#endif
        aio_value *return_value = parse_value_string(return_value_string, context_ref, control_graph);
#ifdef AIO_RETURN_TASK_DEBUG
        log_info_aio_value(AIO_RETURN_TASK_TAG, "Return value:", return_value);
#endif
        add_aio_value_in_list(output_value_list, return_value);
    }
    throw_error_with_tag(AIO_RETURN_TASK_TAG, "STOP HERE!");
    *control_graph->system_state_ref = AIO_FUNCTION_SYSTEM_STOP;
}