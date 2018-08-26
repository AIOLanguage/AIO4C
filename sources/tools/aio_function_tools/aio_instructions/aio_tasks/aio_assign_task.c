#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_assign_task.h"
#include "../../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"


#define AIO_ASSIGN_TASK_TAG "AIO_ASSIGN_TASK"

#define AIO_ASSIGN_TASK_DEBUG

#ifdef AIO_ASSIGN_TASK_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"
#include "../../../../../headers/lang/aio_type/aio_type.h"

#endif

aio_function_instruction *new_aio_assign_instruction(
        aio_function_instruction_holder *holder,
        const_string value,
        const_str_hook *variable_name
)
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
#ifdef AIO_ASSIGN_TASK_DEBUG
    log_info_str_hook(AIO_ASSIGN_TASK_TAG, "Destination:", variable_name);
#endif
    //Not null!
    aio_variable *variable = force_get_aio_variable_in_function_control_graph(variable_name, control_graph);
#ifdef AIO_ASSIGN_TASK_DEBUG
    log_info_boolean(AIO_ASSIGN_TASK_TAG, "Imported variable is not null", variable != NULL);
#endif
    const_aio_variable_definition *variable_definition = variable->definition;
    const_str_hook *variable_type = variable_definition->type;
#ifdef AIO_ASSIGN_TASK_DEBUG
    log_info_str_hook(AIO_ASSIGN_TASK_TAG, "Required type:", variable_type);
    log_info_aio_value(AIO_ASSIGN_TASK_TAG, "Previous value:", variable->value);
#endif
    //Parse value:
    const_string value_string = task->value;
#ifdef AIO_ASSIGN_TASK_DEBUG
    log_info_string(AIO_ASSIGN_TASK_TAG, "Parse src:", value_string);
#endif
    aio_value *value = parse_value_string(value_string, control_graph->context_ref, control_graph);
#ifdef AIO_ASSIGN_TASK_DEBUG
    log_info_aio_value(AIO_ASSIGN_TASK_TAG, "Parsed value:", value);
#endif
    //Cast value:
    variable->init_type = AIO_VARIABLE_INITIALIZED;
    if (is_aio_type_initialized(variable_type)) {
        variable->value = cast_to_type(value, variable_type);
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_aio_value(value);
#ifdef AIO_ASSIGN_TASK_DEBUG
        log_info_aio_value(AIO_ASSIGN_TASK_TAG, "Initialized variable value:", variable->value);
#endif
    } else {
        variable->definition->type = value->type;
        variable->value = value;
#ifdef AIO_ASSIGN_TASK_DEBUG
        log_info_aio_value(AIO_ASSIGN_TASK_TAG, "Not initialized variable value:", variable->value);
#endif
    }
}