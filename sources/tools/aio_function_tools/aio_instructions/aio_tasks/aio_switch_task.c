#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../../headers/lib/utils/collections/lists/string_list.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_switch_task.h"
#include "../../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"

#define AIO_SWITCH_TASK_DEBUG

#ifdef AIO_SWITCH_TASK_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"

#endif

#define AIO_SWITCH_TASK_TAG "AIO_SWITCH_TASK"

aio_function_instruction *new_aio_switch_instruction(
        struct aio_function_instruction_holder *holder, const_string switch_value,
        string_list *case_keys, struct aio_function_instruction_holder **case_holders,
        struct aio_function_instruction_holder *else_holder)
{
    aio_function_instruction *instruction = new_aio_function_instruction(holder, AIO_SWITCH_TASK);
    //Init task:
    aio_switch_task *task = new_object(sizeof(aio_switch_task));
    task->switch_value = switch_value;
    task->case_keys = case_keys;
    task->case_holders = case_holders;
    task->else_holder = else_holder;
    instruction->get.switch_task = task;
    return instruction;
}

void perform_aio_switch_instruction(const_aio_function_instruction *instruction,
                                    const_aio_function_control_graph *control_graph)
{
    //Extract task:
    const aio_switch_task *task = instruction->get.switch_task;
    const_string switch_value_string = task->switch_value;
    const_string_list *case_value_string_list = task->case_keys;
    const_string_array case_value_strings = case_value_string_list->strings;
    aio_function_instruction_holder **case_holders = task->case_holders;
    const size_t number_of_cases = case_value_string_list->size;
    //Extract control graph:
    aio_bundle *bundle_ref = control_graph->bundle_ref;
    const_aio_context *context_ref = control_graph->context_ref;
    //Prepare to switch:
    boolean was_successful_case = FALSE;
    //Parse switch value:
#ifdef AIO_SWITCH_TASK_DEBUG
    log_info(AIO_SWITCH_TASK_TAG, "Start to parse switch value...");
#endif
    aio_value *switch_value = parse_value_string(switch_value_string, context_ref, control_graph);
#ifdef AIO_SWITCH_TASK_DEBUG
    log_info_aio_value(AIO_SWITCH_TASK_TAG, "SWITCH_VALUE", switch_value);
    log_info_int(AIO_SWITCH_TASK_TAG, "Number of cases:", number_of_cases);
#endif
    //Parse each case value:
    for (int i = 0; i < number_of_cases; ++i) {
        const_string case_value_string = case_value_strings[i];
#ifdef AIO_SWITCH_TASK_DEBUG
        log_info_string(AIO_SWITCH_TASK_TAG, "Case string:", case_value_string);
#endif
        aio_value *case_value = parse_value_string(case_value_string, context_ref, control_graph);
        throw_error_with_tag(AIO_SWITCH_TASK_TAG, "STOP HERE!");
        if (are_equal_aio_values(switch_value, case_value)) {
            was_successful_case = TRUE;
            const_aio_function_instruction_holder *case_holder = case_holders[i];
            inflate_new_aio_function_control_graph(control_graph, case_holder, bundle_ref, context_ref);
        }
    }
    if (!was_successful_case) {
        const_aio_function_instruction_holder *else_holder = task->else_holder;
        inflate_new_aio_function_control_graph(control_graph, else_holder, bundle_ref, context_ref);
    }
}