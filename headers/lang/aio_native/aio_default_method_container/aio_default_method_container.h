#ifndef AIO_DEFAULT_METHOD_CONTAINER_H
#define AIO_DEFAULT_METHOD_CONTAINER_H

#include "../../aio_method/result/aio_result.h"
#include "../../../lib/utils/boolean_utils/boolean_utils.h"

boolean is_default_int_method(const_string method_name, aio_result *result);

boolean is_default_double_method(const_string method_name, aio_result *result);

boolean is_default_string_method(const_string *method_name, aio_result *result);

#endif //AIO_DEFAULT_METHOD_CONTAINER_H