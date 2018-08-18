#include "../../../headers/tools/aio_control_graph/aio_control_graph.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"

aio_control_graph *new_aio_control_graph(aio_control_graph *parent, aio_instruction_holder *holder,
                                         aio_bundle *bundle_ref){
    //Extract holder materials:
    aio_instruction_list *instruction_list = holder->instruction_list;
    aio_variable_definition_map *variable_definition_map = holder->variable_definition_map;
    aio_variable_map *variable_map = upbuild_variable_map_by_definitions(variable_definition_map);
    //Build graph:
    aio_control_graph *graph = new_object(sizeof(aio_control_graph));
    graph->parent = parent;
    graph->variable_map = variable_map;
    graph->instruction_list = instruction_list;
    graph->bundle_ref = bundle_ref;
    return graph;
}

void inflate_aio_control_grapf(aio_control_graph *parent, aio_instruction_holder *holder, aio_bundle *bundle_ref);

void free_aio_control_graph(aio_control_graph *graph);