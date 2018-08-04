#ifndef AIO_FUNCTION_DEFINITION_BUILDER_H
#define AIO_FUNCTION_DEFINITION_BUILDER_H

#include "aio_function_definition.h"
#include "../../../lib/utils/boolean_utils/boolean_utils.h"

aio_function_definition *build_aio_method_definition(string method_name, string_list *source_code, int start_index);

boolean is_method_in_the_same_file(string expression);

boolean is_method_in_the_other_file(string expression);

#endif //AIO_FUNCTION_DEFINITION_BUILDER_H