#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_if_task.h"
#include "../../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"
#include "../../../../../headers/lib/utils/log_utils/log_utils.h"

#define AIO_IF_TASK_DEBUG

#define AIO_IF_TASK_TAG "AIO_IF_TASK"

#ifdef AIO_IF_TASK_DEBUG

#endif

aio_function_instruction *new_aio_if_instruction(
        aio_function_instruction_holder *holder,
        const_string if_condition,
        aio_function_instruction_holder *true_holder,
        aio_function_instruction_holder *false_holder
)
{
    aio_function_instruction *instruction = new_aio_function_instruction(holder, AIO_IF_TASK);
    //Init task:
    aio_if_task *task = new_object(sizeof(aio_if_task));
    task->if_condition = if_condition;
    task->true_holder = true_holder;
    task->false_holder = false_holder;
    instruction->get.if_task = task;
    return instruction;
}

void perform_aio_if_instruction(
        const_aio_function_instruction *instruction,
        const_aio_function_control_graph *control_graph
)
{
    //Extract control graph:
    aio_bundle *bundle_ref = control_graph->bundle_ref;
    const_aio_context *context_ref = control_graph->context_ref;
    //Extract task:
    const aio_if_task *task = instruction->get.if_task;
    const_string condition_string = task->if_condition;
#ifdef AIO_IF_TASK_DEBUG
    log_info_string(AIO_IF_TASK_TAG, "If condition string:", condition_string);
#endif
    aio_value *condition_value = parse_value_string(condition_string, control_graph->context_ref, control_graph);
    aio_value *boolean_condition_value = cast_to_boolean(condition_value);
    const_boolean is_true = boolean_condition_value->get.boolean_acc;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_aio_value(boolean_condition_value);
    //------------------------------------------------------------------------------------------------------------------
#ifdef AIO_IF_TASK_DEBUG
    log_info_boolean(AIO_IF_TASK_TAG, "Is true:", is_true);
#endif
    if (is_true) {
#ifdef AIO_IF_TASK_DEBUG
        log_info(AIO_IF_TASK_TAG, "Create true branch...");
#endif
        const_aio_function_instruction_holder *true_holder = task->true_holder;
        inflate_new_aio_function_control_graph(control_graph, true_holder, bundle_ref, context_ref);
    } else {
#ifdef AIO_IF_TASK_DEBUG
        log_info(AIO_IF_TASK_TAG, "Try to create false branch...");
#endif
        const_aio_function_instruction_holder *false_holder = task->false_holder;
        if (false_holder) {
#ifdef AIO_IF_TASK_DEBUG
            log_info(AIO_IF_TASK_TAG, "False branch is exist!");
#endif
            inflate_new_aio_function_control_graph(control_graph, false_holder, bundle_ref, context_ref);
        }
    }
}