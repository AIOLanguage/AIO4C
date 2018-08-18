#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../headers/tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h"
#include "../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction_holder.h"
#include "../../../../headers/lang/aio_function/aio_variable/aio_definition/aio_variable_definition.h"

const_aio_control_graph *new_aio_control_graph(aio_control_graph *parent, aio_function_instruction_holder *holder,
                                               aio_bundle *bundle_ref) {
    //Extract holder materials:
    const_aio_function_instruction_list *instruction_list = holder->instruction_list;
    const_aio_variable_definition_list *variable_definition_list = holder->variable_definition_list;
    const_aio_variable_list *variable_list = upbuild_variable_map_by_definitions(variable_definition_list);
    //Build graph:
    aio_control_graph *graph = new_object(sizeof(aio_control_graph));
    graph->parent = parent;
    graph->variable_map = variable_list;
    graph->instruction_list = instruction_list;
    graph->bundle_ref = bundle_ref;
    return graph;
}

void inflate_aio_control_graph(aio_control_graph *parent, aio_function_instruction_holder *holder,
                               aio_bundle *bundle_ref) {

}

void free_aio_control_graph(aio_control_graph *graph) {
    
}