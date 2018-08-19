#ifndef AIO_CONTROL_GRAPH_H
#define AIO_CONTROL_GRAPH_H

#include "../../../lang/aio_function/aio_bundle/aio_bundle.h"
#include "../../../lang/aio_function/aio_variable/aio_variable.h"
#include "../aio_instructions/aio_function_instruction.h"

typedef struct aio_control_graph {
    struct aio_control_graph *parent;
    const_aio_variable_list *variable_map;
    const_aio_function_instruction_list *instruction_list;
    aio_bundle *bundle_ref;
} aio_control_graph;

typedef const aio_control_graph const_aio_control_graph;

const_aio_control_graph * new_aio_control_graph(aio_control_graph *parent, aio_function_instruction_holder *holder,
                                                aio_bundle *bundle_ref);

void inflate_aio_control_graph(aio_control_graph *parent, aio_function_instruction_holder *holder,
                               aio_bundle *bundle_ref);

void free_aio_control_graph(aio_control_graph *graph);

#endif //AIO_CONTROL_GRAPH_H