#ifndef AIO_FUNCTION_DEFINITION_BUILDER_H
#define AIO_FUNCTION_DEFINITION_BUILDER_H

#include "aio_function_definition.h"
#include "../../../lib/utils/boolean_utils/boolean_utils.h"

aio_function_definition *build_aio_function_definition(const_string source_code, int *start_index_ref);

#endif //AIO_FUNCTION_DEFINITION_BUILDER_H