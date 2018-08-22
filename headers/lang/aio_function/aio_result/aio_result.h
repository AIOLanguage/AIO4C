#ifndef AIO_RESULT_H
#define AIO_RESULT_H

#include "../../../lib/utils/string_utils/string_utils.h"
#include "../aio_value/aio_value.h"
#include "../../../lib/utils/str_hook/str_hook.h"

typedef struct aio_result {
    struct aio_value *value;
    struct str_hook *rest;
} aio_result;

struct aio_result *new_aio_result(struct aio_value *value, struct str_hook *rest);

struct aio_result *new_aio_int_result(const int int_acc, struct str_hook *rest);

struct aio_result *new_aio_double_result(const double double_acc, struct str_hook *rest);

struct aio_result *new_aio_string_result(char *string_acc, struct str_hook *rest);

struct aio_result *new_aio_boolean_result(const _Bool boolean_acc, struct str_hook *rest);

void free_aio_result(struct aio_result *result);

#endif //AIO_RESULT_H