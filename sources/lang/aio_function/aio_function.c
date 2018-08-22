#include <mem.h>
#include <stdio.h>
#include <process.h>
#include <malloc.h>
#include "../../../headers/lang/aio_function/aio_bundle/aio_bundle.h"
#include "../../../headers/lang/aio_context/aio_context.h"
#include "../../../headers/lang/aio_function/aio_function.h"
#include "../../../headers/lang/aio_function/aio_value/aio_value.h"

aio_value_list *invoke_aio_function(const_aio_function_definition *definition, aio_bundle *bundle,
                                    const_aio_context *context) {
    aio_function_control_graph *parent_graph = NULL;
    inflate_new_aio_root_function_control_graph(parent_graph, root_holder, bundle, context);
    return bundle->output_values;
}