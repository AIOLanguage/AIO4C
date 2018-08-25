#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_loop_task.h"
#include "../../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"

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

static const_boolean is_condition_performs(const_string loop_condition_string, const_aio_context *context_ref) {
    aio_value *condition_value = parse_value_string(loop_condition_string, context_ref, NULL);
    aio_value *boolean_condition_value = cast_to_boolean(condition_value);
    const_boolean is_true = boolean_condition_value->get.boolean_acc;
    return is_true;
}

void perform_aio_loop_instruction(const_aio_function_instruction *instruction,
                                  const_aio_function_control_graph *control_graph) {
    const aio_loop_task *task = instruction->get.loop_task;
    //Extract control graph:
    aio_bundle *bundle_ref = control_graph->bundle_ref;
    const_aio_context *context_ref = control_graph->context_ref;
    aio_function_system_state *system_state = control_graph->system_state_ref;
    //Make init:
    const_aio_function_instruction_holder *init_holder = task->init_holder;
    const_aio_function_control_graph *init_control_graph = new_aio_function_control_graph(control_graph, init_holder,
                                                                                          bundle_ref, context_ref,
                                                                                          system_state);
    perform_aio_function_instructions(init_control_graph);
    //Make cycle:
    const_aio_function_instruction_holder *cycle_holder = task->cycle_holder;
    const_string loop_condition_string = task->loop_condition;
    while (is_condition_performs(loop_condition_string, context_ref)) {
        inflate_new_aio_function_control_graph(control_graph, cycle_holder, bundle_ref, context_ref);
        if (*system_state == AIO_FUNCTION_SYSTEM_BREAK) {
            *system_state = AIO_FUNCTION_SYSTEM_MAKE;
            break;
        }
        if (*system_state == AIO_FUNCTION_SYSTEM_CONTINUE) {
            *system_state = AIO_FUNCTION_SYSTEM_MAKE;
            continue;
        }
        if (*system_state == AIO_FUNCTION_SYSTEM_STOP) {
            break;
        }
    }
    free_aio_control_graph(init_control_graph);
}