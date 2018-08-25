#ifndef AIO_FUNCTION_CONTROL_GRAPH_H
#define AIO_FUNCTION_CONTROL_GRAPH_H

#include "../../../lang/aio_function/aio_bundle/aio_bundle.h"
#include "../../../lang/aio_function/aio_variable/aio_variable.h"
#include "../aio_instructions/aio_function_instruction.h"
#include "../../../lang/aio_context/aio_context.h"

typedef enum aio_function_system_state {
    AIO_FUNCTION_SYSTEM_MAKE, AIO_FUNCTION_SYSTEM_BREAK, AIO_FUNCTION_SYSTEM_CONTINUE, AIO_FUNCTION_SYSTEM_STOP
} aio_function_system_state;


typedef struct aio_function_control_graph {
    const struct aio_function_control_graph *parent;
    const struct aio_variable_list *variable_list;
    const struct aio_function_instruction_list *instruction_list;
    const struct aio_context *context_ref;
    aio_bundle *bundle_ref;
    aio_function_system_state *system_state_ref;
} aio_function_control_graph;

typedef const aio_function_control_graph const_aio_function_control_graph;

const_aio_function_control_graph *new_aio_function_control_graph(const_aio_function_control_graph *parent,
                                                                 const struct aio_function_instruction_holder *holder,
                                                                 aio_bundle *bundle_ref,
                                                                 const struct aio_context *context_ref,
                                                                 aio_function_system_state *system_state_ref);

void inflate_new_aio_function_control_graph(const_aio_function_control_graph *parent,
                                            const struct aio_function_instruction_holder *holder,
                                            aio_bundle *bundle_ref,
                                            const struct aio_context *context);

void inflate_new_aio_root_function_control_graph(const struct aio_function_control_graph *parent,
                                                 const struct  aio_function_definition *function_definition,
                                                 struct aio_bundle *bundle_ref,
                                                 const struct aio_context *context);

void perform_aio_function_instructions(const_aio_function_control_graph *control_graph);

void free_aio_control_graph(const_aio_function_control_graph *graph);

#endif //AIO_FUNCTION_CONTROL_GRAPH_H