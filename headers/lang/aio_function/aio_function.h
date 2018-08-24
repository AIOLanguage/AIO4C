#ifndef AIO_FUNCTION_H
#define AIO_FUNCTION_H

#include "../aio_context/aio_context.h"
#include "aio_variable/aio_variable.h"
#include "../../tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h"
#include "../../lib/utils/memory_utils/memory_utils.h"

struct aio_value_list *invoke_static_function_in_context(
        const struct aio_context *context,
        const struct str_hook *function_name,
        struct aio_bundle *bundle
);

struct aio_value_list *invoke_aio_function(
        const struct aio_function_definition *definition,
        struct aio_bundle *bundle,
        const struct aio_context *context
);

#endif //AIO_FUNCTION_H