#ifndef AIO_RESULT_H
#define AIO_RESULT_H

#include "../../../lib/utils/string_utils/string_utils.h"
#include "../aio_value/aio_value.h"
#include "../../../lib/utils/string_hook/str_hook.h"

typedef struct aio_result {
    aio_value *value;
    str_hook *rest;
} aio_result;

aio_result *new_aio_result(aio_value *value, string rest);

aio_result *new_aio_int_result(const int int_acc, str_hook *rest);

aio_result *new_aio_dou_result(const double double_acc, str_hook *rest);

aio_result *new_aio_str_result(string string_acc, str_hook *rest);

aio_result *new_aio_boo_result(const_boolean boolean_acc, str_hook *rest);

void free_aio_result(aio_result *result);

#endif //AIO_RESULT_H