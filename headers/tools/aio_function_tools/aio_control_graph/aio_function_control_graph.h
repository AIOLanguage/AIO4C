#ifndef AIO_FUNCTION_CONTROL_GRAPH_H
#define AIO_FUNCTION_CONTROL_GRAPH_H

#include "../../../lang/aio_function/aio_bundle/aio_bundle.h"
#include "../../../lang/aio_function/aio_variable/aio_variable.h"
#include "../aio_instructions/aio_function_instruction.h"
#include "../../../lang/aio_context/aio_context.h"

typedef struct aio_function_control_graph {
    const struct aio_function_control_graph *parent;
    const_aio_variable_list *variable_list;
    const_aio_function_instruction_list *instruction_list;
    const_aio_context *context_ref;
    aio_bundle *bundle_ref;
} aio_function_control_graph;

typedef const aio_function_control_graph const_aio_function_control_graph;

const_aio_function_control_graph *new_aio_control_graph(const_aio_function_control_graph *parent,
                                                        const_aio_function_instruction_holder *holder,
                                                        aio_bundle *bundle_ref, const_aio_context *context_ref);

void inflate_new_aio_control_graph(const_aio_function_control_graph *parent,
                                   const_aio_function_instruction_holder *holder,
                                   aio_bundle *bundle_ref,
                                   const_aio_context *context);

void inflate_new_aio_root_control_graph(aio_function_control_graph *parent,
                                        const_aio_function_instruction_holder *holder,
                                        aio_bundle *bundle_ref, const_aio_context *context);

void perform_aio_instructions(const_aio_function_control_graph *control_graph);

void free_aio_control_graph(const_aio_function_control_graph *graph);

#endif //AIO_FUNCTION_CONTROL_GRAPH_H