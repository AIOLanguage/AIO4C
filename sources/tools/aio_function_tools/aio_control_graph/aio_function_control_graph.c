#include <mem.h>
#include <malloc.h>
#include <tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h>
#include <tools/aio_function_tools/aio_instructions/aio_function_instruction_holder.h>
#include <lang/aio_function/aio_bundle/aio_bundle.h>
#include <lang/aio_context/aio_context.h>
#include <tools/aio_function_tools/aio_instructions/aio_function_instruction.h>
#include <lang/aio_function/aio_variable/aio_definition/aio_variable_definition.h>
#include <lang/aio_function/aio_variable/aio_variable.h>
#include <lib/utils/memory_utils/memory_utils.h>
#include <lang/aio_function/aio_function_definition/aio_function_definition.h>
#include <tools/aio_function_tools/aio_control_graph/aio_function_control_graph_management.h>

#define AIO_CONTROL_GRAPH_DEBUG

#define AIO_CONTROL_GRAPH_TAG "AIO_CONTROL_GRAPH"

#define START_AIO_VALUE NULL

#ifdef AIO_CONTROL_GRAPH_DEBUG

#endif


static const_aio_variable_list *upbuild_variable_map_by_definitions(const_aio_variable_definition_list *list)
{
    //Extract definition list:
    const size_t definition_list_size = list->size;
    aio_variable_definition **definitions = list->definitions;
    //Prepare to building:
    aio_variable_list *variable_list = new_aio_variable_list();
    for (int i = 0; i < definition_list_size; ++i) {
        aio_variable_definition *definition = definitions[i];
        aio_field *new_variable = new_aio_variable_by_definition(definition, START_AIO_VALUE);
        add_aio_variable_in_list(variable_list, new_variable);
    }
    return variable_list;
}

const_aio_function_control_graph *new_aio_function_control_graph(
        const_aio_function_control_graph *parent,
        const_aio_function_instruction_holder *holder,
        aio_bundle *bundle_ref,
        const_aio_context *context_ref,
        aio_function_system_state *system_state_ref
)
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

void inflate_new_aio_root_function_control_graph(
        const_aio_function_control_graph *parent,
        const_aio_function_definition *function_definition,
        aio_bundle *bundle_ref,
        const_aio_context *context
)
{
    //Init start system state:
    aio_function_system_state system_state = AIO_FUNCTION_SYSTEM_MAKE;
    const_aio_function_instruction_holder *root_holder = function_definition->root_holder;
    const_aio_function_control_graph *control_graph = new_aio_function_control_graph(
            parent,
            root_holder,
            bundle_ref,
            context,
            &system_state
    );
    put_arg_values_in_aio_control_graph(control_graph, function_definition);
    perform_aio_function_instructions(control_graph);
    free_aio_control_graph(control_graph);
}

void inflate_new_aio_function_control_graph(
        const_aio_function_control_graph *parent,
        const_aio_function_instruction_holder *holder,
        aio_bundle *bundle
)
{
    const_aio_function_control_graph *control_graph = new_aio_function_control_graph(
            parent,
            holder,
            bundle,
            parent->context_ref,
            parent->system_state_ref
    );
    perform_aio_function_instructions(control_graph);
    free_aio_control_graph(control_graph);
}

void free_aio_control_graph(const_aio_function_control_graph *graph)
{
    free_aio_variable_list(graph->variable_list);
    free((void *) graph);
}