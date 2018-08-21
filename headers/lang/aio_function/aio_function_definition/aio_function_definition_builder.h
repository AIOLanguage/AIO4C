#ifndef AIO_FUNCTION_DEFINITION_BUILDER_H
#define AIO_FUNCTION_DEFINITION_BUILDER_H

#include "aio_function_definition.h"
#include "../../../lib/utils/boolean_utils/boolean_utils.h"

const struct aio_function_definition *conjure_aio_function_definition(const char *source_code, int *start_index_ref);

#endif //AIO_FUNCTION_DEFINITION_BUILDER_H