#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_if_task.h"
#include "../../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"

aio_function_instruction * new_aio_if_instruction(
        struct aio_function_instruction_holder *holder, const_string if_condition,
        struct aio_function_instruction_holder *true_holder, struct aio_function_instruction_holder *false_holder) {
    aio_function_instruction *instruction = new_aio_function_instruction(holder, AIO_IF_TASK);
    //Init task:
    aio_if_task *task = new_object(sizeof(aio_if_task));
    task->if_condition = if_condition;
    task->true_holder = true_holder;
    task->false_holder = false_holder;
    instruction->get.if_task = task;
    return instruction;
}

void perform_aio_if_instruction(const_aio_function_instruction *instruction,
                                const_aio_function_control_graph *control_graph) {
    const aio_if_task *task = instruction->get.if_task;
    const_string condition_string = task->if_condition;
    const_aio_function_instruction_holder *branch_holder = NULL;
    aio_value *condition_value = parse_value_string(condition_string, control_graph->context_ref, NULL);
    aio_value *boolean_condition_value = cast_to_boolean(condition_value);
    const_boolean is_true = boolean_condition_value->get.boolean_acc;
    if (is_true) {
        branch_holder = task->true_holder;
    } else {
        branch_holder = task->false_holder;
    }
    aio_bundle *bundle_ref = control_graph->bundle_ref;
    const_aio_context *context_ref = control_graph->context_ref;
    inflate_new_aio_function_control_graph(control_graph, branch_holder, bundle_ref, context_ref);
}