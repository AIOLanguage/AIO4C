#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_assign_task.h"
#include "../../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"

aio_function_instruction *new_aio_assign_instruction(
        aio_function_instruction_holder *holder, const_string value,
        const_str_hook *variable_name)
{
    aio_function_instruction *instruction = new_aio_function_instruction(holder, AIO_ASSIGN_TASK);
    //Init task:
    aio_assign_task *task = new_object(sizeof(aio_assign_task));
    task->value = value;
    task->variable_name = variable_name;
    instruction->get.assign_task = task;
    return instruction;
}

void perform_aio_assign_instruction(const_aio_function_instruction *instruction,
                                    const_aio_function_control_graph *control_graph)
{
    const aio_assign_task *task = instruction->get.assign_task;
    const_str_hook *variable_name = task->variable_name;
    //Not null!
    aio_variable *variable = get_aio_variable_in_function_control_graph(variable_name, control_graph);
    const_aio_variable_definition *variable_definition = variable->definition;
    const_str_hook *variable_type = variable_definition->type;
    //Parse value:
    const_string value_string = task->value;
    aio_value *value = parse_value_string(value_string, control_graph->context_ref, NULL);
    //Cast value:
    variable->init_type = AIO_VARIABLE_INITIALIZED;
    variable->value = cast_to_type(value, variable_type);
}