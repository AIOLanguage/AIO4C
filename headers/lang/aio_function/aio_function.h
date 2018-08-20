#ifndef AIO_FUNCTION_H
#define AIO_FUNCTION_H

#include "../aio_context/aio_context.h"
#include "aio_variable/aio_variable.h"
#include "../../tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h"
#include "../../lib/utils/memory_utils/memory_utils.h"

aio_value_list *invoke_aio_function(const_aio_function_definition *definition, aio_bundle *bundle,
                                    const_aio_context *context);

#endif //AIO_FUNCTION_H