#ifndef AIO_FUNCTION_REPRODUCER_H
#define AIO_FUNCTION_REPRODUCER_H


#include "../../../lang/aio_function/aio_bundle/aio_bundle.h"
#include "../../../lang/aio_context/aio_context.h"
#include "../../../lang/aio_function/aio_function.h"

void reproduce_function(aio_context *context, aio_function_definition *function_definition, aio_function *function,
                        aio_bundle *bundle);

#endif //AIO_FUNCTION_REPRODUCER_H