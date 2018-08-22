#include <process.h>
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../headers/tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"

#define AIO_CONTROL_GRAPH_DEBUG

#define AIO_CONTROL_GRAPH_TAG "AIO_CONTROL_GRAPH"

#ifdef AIO_CONTROL_GRAPH_DEBUG

#include "../../../../headers/lib/utils/log_utils/log_utils.h"
#include "../../../../headers/lang/aio_type/aio_type.h"

#endif

static void put_arg_values_in_aio_control_graph(
        const_aio_function_control_graph *control_graph,
        const_aio_function_definition *function_definition
)
{
#ifdef AIO_CONTROL_GRAPH_DEBUG
    log_info(AIO_CONTROL_GRAPH_TAG, "Putting args...");
#endif
    //Get input arguments:
    aio_value_list *input_value_list = control_graph->bundle_ref->input_values;
    aio_value_array input_values = input_value_list->values;
    //Get variable list in function:
    const_aio_variable_list *list = control_graph->variable_list;
    aio_variable_array variables = list->variables;
    //First indexes are args:
    //Check number of input values:
    const size_t input_value_list_size = input_value_list->size;
    const_boolean is_same_number_of_args = function_definition->number_of_args == input_value_list_size;
#ifdef AIO_CONTROL_GRAPH_DEBUG
    log_info_boolean(AIO_CONTROL_GRAPH_TAG, "Matches number input values and required args", is_same_number_of_args);
#endif
    if (is_same_number_of_args) {
        //Put input values:
        for (int i = 0; i < input_value_list_size; ++i) {
            //Extract input value:
            aio_value *input_value = input_values[i];
            str_hook *input_type = input_value->type;
            //Extract argument:
            aio_variable *argument = variables[i];
            const_aio_variable_definition *argument_definition = argument->definition;
            str_hook *required_type = argument_definition->type;
#ifdef AIO_CONTROL_GRAPH_DEBUG
            log_info(AIO_CONTROL_GRAPH_TAG, "--------------------------------------");
            log_info_str_hook(AIO_CONTROL_GRAPH_TAG, "Required type:", required_type);
            log_info_str_hook(AIO_CONTROL_GRAPH_TAG, "Input type:", input_type);
#endif
            if (!are_equal_hooked_str(required_type, input_type)) {
#ifdef AIO_CONTROL_GRAPH_DEBUG
                log_info_str_hook(AIO_CONTROL_GRAPH_TAG, "Cast to type:", required_type);
#endif
                aio_value *casted_value = cast_to_type(input_value, required_type);
#ifdef AIO_CONTROL_GRAPH_DEBUG
                const_str_hook *type = casted_value->type;
                if (is_hook_equals_str(type, INTEGER)) {
                    log_info_int(AIO_CONTROL_GRAPH_TAG, "Casted value:", casted_value->get.int_acc);
                }
                if (is_hook_equals_str(type, DOUBLE)) {
                    log_info_double(AIO_CONTROL_GRAPH_TAG, "Casted value:", casted_value->get.double_acc);
                }
                if (is_hook_equals_str(type, STRING)) {
                    log_info_string(AIO_CONTROL_GRAPH_TAG, "Casted value:", casted_value->get.string_acc);
                }
                if (is_hook_equals_str(type, BOOLEAN)) {
                    log_info_boolean(AIO_CONTROL_GRAPH_TAG, "Casted value:", casted_value->get.boolean_acc);
                }
#endif
                argument->value = casted_value;
            }
        }
    } else {
        throw_error_with_tag(AIO_CONTROL_GRAPH_TAG, "Invalid number of args!");
    }
    exit(1);
}

const_aio_function_control_graph *new_aio_function_control_graph(const_aio_function_control_graph *parent,
                                                                 const_aio_function_instruction_holder *holder,
                                                                 aio_bundle *bundle_ref, const_aio_context *context_ref,
                                                                 aio_function_system_state *system_state_ref)
{
    //Extract holder materials:
    const_aio_function_instruction_list *instruction_list = holder->instruction_list;
    const_aio_variable_definition_list *variable_definition_list = holder->variable_definition_list;
    const_aio_variable_list *variable_list = upbuild_variable_map_by_definitions(variable_definition_list);
    //Build graph:
    aio_function_control_graph *graph = new_object(sizeof(aio_function_control_graph));
    graph->parent = parent;
    graph->variable_list = variable_list;
    graph->instruction_list = instruction_list;
    graph->bundle_ref = bundle_ref;
    graph->context_ref = context_ref;
    graph->system_state_ref = system_state_ref;
    return graph;
}

void inflate_new_aio_root_function_control_graph(const_aio_function_control_graph *parent,
                                                 const_aio_function_definition *function_definition,
                                                 aio_bundle *bundle_ref,
                                                 const_aio_context *context)
{
    //Init start system state:
#ifdef AIO_CONTROL_GRAPH_DEBUG
    log_info_str_hook(AIO_CONTROL_GRAPH_TAG, "Start to inflate root graph in function:", function_definition->name);
#endif
    aio_function_system_state system_state = AIO_FUNCTION_SYSTEM_MAKE;
    const_aio_function_instruction_holder *root_holder = function_definition->root_holder;
    const_aio_function_control_graph *control_graph
            = new_aio_function_control_graph(parent, root_holder, bundle_ref, context, &system_state);
    put_arg_values_in_aio_control_graph(control_graph, function_definition);
    perform_aio_function_instructions(control_graph);
    free_aio_control_graph(control_graph);
}

void inflate_new_aio_function_control_graph(const_aio_function_control_graph *parent,
                                            const_aio_function_instruction_holder *holder,
                                            aio_bundle *bundle_ref, const_aio_context *context)
{
    const_aio_function_control_graph *control_graph = new_aio_function_control_graph(parent, holder, bundle_ref,
                                                                                     context,
                                                                                     parent->system_state_ref);
    perform_aio_function_instructions(control_graph);
    free_aio_control_graph(control_graph);
}

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

void free_aio_control_graph(const_aio_function_control_graph *graph)
{

}