#include <tools/aio_function_tools/aio_instructions/aio_function_instruction.h>
#include <lib/utils/string_utils/string_utils.h>
#include <tools/aio_function_tools/aio_instructions/aio_tasks/aio_if_task.h>
#include <lib/utils/memory_utils/memory_utils.h>
#include <lang/aio_function/aio_value/aio_value.h>
#include <tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h>

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
    //Extract task:
    const aio_if_task *task = instruction->get.if_task;
    const_string condition_string = task->if_condition;
    aio_value *condition_value = parse_value_string(condition_string, control_graph);
    aio_value *boolean_condition_value = cast_to_boolean(condition_value);
    const_boolean is_true = boolean_condition_value->get.boolean_acc;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_aio_value(boolean_condition_value);
    //------------------------------------------------------------------------------------------------------------------
    if (is_true) {
        const_aio_function_instruction_holder *true_holder = task->true_holder;
        inflate_new_aio_function_control_graph(control_graph, true_holder, bundle_ref);
    } else {
        const_aio_function_instruction_holder *false_holder = task->false_holder;
        if (false_holder) {
            inflate_new_aio_function_control_graph(control_graph, false_holder, bundle_ref);
        }
    }
}