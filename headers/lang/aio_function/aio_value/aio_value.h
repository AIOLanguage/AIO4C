#ifndef AIO_VALUE_H
#define AIO_VALUE_H

#include "../../../lib/utils/string_utils/string_utils.h"

/**
 * Value.
 */

typedef union aio_value {
    int int_acc;
    double double_acc;
    string string_acc;
    boolean boolean_acc;
    void *reference;
} aio_value;

aio_value *new_aio_value(const_string undefined_value);

aio_value *new_aio_value_as_int(const int int_acc);

aio_value *new_aio_value_as_double(const double double_acc);

aio_value *new_aio_value_as_string(string string_acc);

aio_value *new_aio_value_as_boolean(const_boolean boolean_acc);

void free_aio_value(aio_value *value);

/**
 * List.
 */

typedef struct aio_value_list {
    size_t capacity;
    size_t size;
    aio_value **values;
} aio_value_list;

aio_value_list *new_aio_value_list();

void add_aio_value_in_list(aio_value_list *string_list, aio_value *value);

void free_aio_values_in_list(aio_value_list *list);

void free_aio_value_list(aio_value_list *list);

#endif //AIO_VALUE_H