#include <malloc.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lang/aio_function/aio_result/aio_result.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"

aio_result *new_aio_result(aio_value *value, str_hook *rest)
{
    aio_result *result = new_object(sizeof(aio_result));
    result->value = value;
    result->rest = rest;
    return result;
}


aio_result *new_aio_int_result(const int int_acc, str_hook *rest)
{
    return new_aio_result(new_aio_int_value(int_acc), rest);
}

aio_result *new_aio_double_result(const double double_acc, str_hook *rest)
{
    return new_aio_result(new_aio_double_value(double_acc), rest);
}

aio_result *new_aio_string_result(string string_acc, str_hook *rest)
{
    return new_aio_result(new_aio_string_value(string_acc), rest);
}

aio_result *new_aio_boolean_result(const_boolean boolean_acc, str_hook *rest)
{
    return new_aio_result(new_aio_boolean_value(boolean_acc), rest);
}

void free_aio_result(aio_result *result)
{

}