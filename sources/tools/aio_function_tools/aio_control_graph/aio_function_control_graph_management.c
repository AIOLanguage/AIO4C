#include <mem.h>
#include <lang/aio_function/aio_variable/aio_variable.h>
#include <lang/aio_function/aio_function_definition/aio_function_definition.h>
#include <lang/aio_function/aio_value/aio_value.h>
#include <lang/aio_function/aio_variable/aio_definition/aio_variable_definition.h>
#include <lang/aio_function/aio_bundle/aio_bundle.h>
#include <tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h>
#include <tools/aio_function_tools/aio_instructions/aio_function_instruction.h>
#include <lib/utils/str_hook/str_hook.h>
#include <lib/utils/boolean_utils/boolean_utils.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <lib/utils/error_utils/error_utils.h>

#define AIO_FUNCTION_CONTROL_GRAPH_MANAGEMENT_DEBUG

#define AIO_FUNCTION_CONTROL_GRAPH_MANAGEMENT_TAG "AIO_FUNCTION_CONTROL_GRAPH_MANAGEMENT"

#ifdef AIO_FUNCTION_CONTROL_GRAPH_MANAGEMENT_DEBUG

#endif

/**
 *
 *초기화 체크없이 변수를 검색합니다 (Retrieves variable without initialization check).
 * @param variable_name - 변수 이름
 * @param control_graph - 현재 제어 그래프
 * @return 변수
 */

aio_variable *force_get_aio_variable_in_function_control_graph(
        const_str_hook *variable_name,
        const_aio_function_control_graph *control_graph
)
{
    const_aio_variable_list *list = control_graph->variable_list;
    aio_variable *variable = get_aio_variable_in_list_by_name(list, variable_name);
    if (!variable) {
        const_aio_function_control_graph *parent = control_graph->parent;
        if (parent) {
            return force_get_aio_variable_in_function_control_graph(variable_name, parent);
        } else {
            return NULL;
        }
    } else {
        return variable;
    }
}

/**
 *
 *초기화 체크로 변수를 검색합니다 (Retrieves variable without initialization check).
 * @param variable_name - 변수 이름
 * @param control_graph - 현재 제어 그래프
 * @return 변수
 */

aio_variable *get_aio_variable_in_function_control_graph(
        const_str_hook *variable_name,
        const_aio_function_control_graph *control_graph
)
{
    aio_variable *variable = force_get_aio_variable_in_function_control_graph(variable_name, control_graph);
    if (variable) {
        const_boolean is_not_reached_variable_in_graph = variable->init_type == AIO_VARIABLE_NOT_INITIALIZED;
        if (is_not_reached_variable_in_graph) {
            return NULL;
        } else {
            return variable;
        }
    } else {
        return NULL;
    }
}

/**
 * 함수 인수들을 놓습니다 (Set function arguments)
 * @param control_graph - 루트 제어 그래프
 * @param function_definition
 */

void put_arg_values_in_aio_control_graph(
        const_aio_function_control_graph *control_graph,
        const_aio_function_definition *function_definition
)
{
    //입력 인수들을 받다 (Get input arguments):
    aio_value_list *input_value_list = control_graph->bundle_ref->input_values;
    aio_value_array input_values = input_value_list->values;
    //함수에게서 인수 명부를 받다 (Get variable list in function):
    const_aio_variable_list *list = control_graph->variable_list;
    aio_variable_array variables = list->variables;
    //First indexes are args:
    //Check number of input values:
    const size_t input_value_list_size = input_value_list->size;
    const_boolean is_same_number_of_args = function_definition->number_of_args == input_value_list_size;
    if (is_same_number_of_args) {
        //Put input values:
        for (int i = 0; i < input_value_list_size; ++i) {
            //Extract input value:
            aio_value *input_value = input_values[i];
            //Extract argument:
            aio_variable *argument = variables[i];
            const_aio_variable_definition *argument_definition = argument->definition;
            str_hook *required_type = argument_definition->type;
            argument->init_type = AIO_VARIABLE_INITIALIZED;
            argument->value = cast_to_type(input_value, required_type);
        }
    } else {
        throw_error_with_tag(AIO_FUNCTION_CONTROL_GRAPH_MANAGEMENT_TAG, "Invalid number of args!");
    }
}

/**
 * Basically interprets instructions.
 * @param control_graph - current function control graph.
 */

void perform_aio_function_instructions(const_aio_function_control_graph *control_graph)
{
    const_aio_function_instruction_list *instruction_list = control_graph->instruction_list;
    const_aio_function_instruction_array instructions = instruction_list->instructions;
    const size_t list_size = instruction_list->size;
    for (int i = 0; i < list_size; ++i) {
        const aio_function_system_state system_state = *control_graph->system_state_ref;
        if (system_state == AIO_FUNCTION_SYSTEM_MAKE) {
            perform_aio_instruction(instructions[i], control_graph);
        } else {
            break;
        }
    }
}