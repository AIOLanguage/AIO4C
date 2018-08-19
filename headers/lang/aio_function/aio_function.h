#ifndef AIO_FUNCTION_H
#define AIO_FUNCTION_H

#include "../aio_context/aio_context.h"
#include "aio_variable/aio_variable.h"
#include "../../tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h"

typedef struct aio_function {
    aio_bundle *bundle;
    aio_function_definition *definition;
    aio_control_graph *root_control_graph;
} aio_function;

aio_function *new_aio_function(aio_context *aio_context, aio_function_definition *function_definition,
                               aio_bundle *bundle);

void invoke_new_aio_function(const_aio_context *aio_context, const_aio_function_definition *function_definition,
                             aio_bundle *bundle);

void free_aio_function(aio_function *function);

#endif //AIO_FUNCTION_H