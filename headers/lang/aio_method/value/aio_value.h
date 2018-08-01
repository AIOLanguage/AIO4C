#ifndef AIO_VALUE_H
#define AIO_VALUE_H

#include "../../../lib/utils/string_utils/string_utils.h"

typedef union aio_value {
    int int_acc;
    double double_acc;
    string string_acc;
    boolean boolean_acc;
} aio_value;

aio_value *new_aio_value_as_int(int int_acc);

aio_value *new_aio_value_as_double(double double_acc);

aio_value *new_aio_value_as_string(string string_acc);

aio_value *new_aio_value_as_boolean(boolean boolean_acc);

void delete_aio_value(aio_value *value);

#endif //AIO_VALUE_H