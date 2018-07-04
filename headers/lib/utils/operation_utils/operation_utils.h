#ifndef AIO_OPERATION_UTILS_H
#define AIO_OPERATION_UTILS_H

#include <mem.h>
#include "../boolean_utils/boolean_utils.h"

boolean is_plus_operation(const_string string);

boolean is_multiply_operation(const_string string);

boolean is_concat_operation(const_string string);

boolean is_default_operations(const_string string);

#endif //AIO_OPERATION_UTILS_H