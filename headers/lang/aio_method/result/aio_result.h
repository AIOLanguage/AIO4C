#ifndef AIO_RESULT_H
#define AIO_RESULT_H

#include "../../../lib/utils/string_utils/string_utils.h"
#include "../value/aio_value.h"

typedef struct aio_result {
    aio_value *value;
    string rest;
} aio_result;

aio_result *new_aio_result(aio_value *value, string rest);

void delete_aio_result(aio_result *result);

#endif //AIO_RESULT_H