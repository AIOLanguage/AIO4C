#ifndef AIO_VALUE_H
#define AIO_VALUE_H

#include "../../../lib/utils/string_utils/string_utils.h"
#include "../../../lib/utils/str_hook/str_hook.h"

/**
 * Value.
 */

typedef struct aio_value {

    str_hook *type;

    union {
        int int_acc;
        double double_acc;
        string string_acc;
        boolean boolean_acc;
        void *reference;
    } get;

} aio_value;

typedef aio_value **aio_value_array;

typedef const aio_value **const_aio_value_array;

aio_value *new_aio_value(string undefined_value);

aio_value *new_aio_int_value(const int int_acc);

aio_value *new_aio_double_value(const double double_acc);

aio_value *new_aio_string_value(string string_acc);

aio_value *new_aio_boolean_value(const_boolean boolean_acc);

void free_aio_value(aio_value *value);

/**
 * List.
 */

typedef struct aio_value_list {
    size_t capacity;
    size_t size;
    aio_value_array values;
} aio_value_list;

typedef const aio_value_list const_aio_value_list;

aio_value_list *new_aio_value_list();

void add_aio_value_in_list(aio_value_list *string_list, aio_value *value);

void free_aio_values_in_list(aio_value_list *list);

void free_aio_value_list(aio_value_list *list);

#endif //AIO_VALUE_H