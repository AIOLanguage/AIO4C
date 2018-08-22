#ifndef AIO_VALUE_H
#define AIO_VALUE_H

#include "../../../lib/utils/string_utils/string_utils.h"
#include "../../../lib/utils/str_hook/str_hook.h"

/**
 * Value.
 */

typedef struct aio_value {

    struct str_hook *type;

    union {
        int int_acc;
        double double_acc;
        char *string_acc;
        _Bool boolean_acc;
        void *reference;
    } get;

} aio_value;

struct aio_value *new_aio_value(str_hook* type);

struct aio_value *new_aio_value_by_string(char *undefined_value);

struct aio_value *new_aio_int_value(const int int_acc);

struct aio_value *new_aio_double_value(const double double_acc);

struct aio_value *new_aio_double_value_by_ref(const double *double_acc);

struct aio_value *new_aio_string_value(const char *string_acc);

struct aio_value *new_aio_boolean_value(const _Bool boolean_acc);

struct aio_value *new_aio_reference_value(void *reference);

struct aio_value *new_aio_type_value(void *reference, const struct str_hook *type);

void free_aio_value(struct aio_value *value);

/**
 * List.
 */

typedef struct aio_value_list {
    unsigned int capacity;
    unsigned int size;
    struct aio_value **values;
} aio_value_list;

struct aio_value_list *new_aio_value_list();

void add_aio_value_in_list(struct aio_value_list *string_list, struct aio_value *value);

void free_aio_value_list(struct aio_value_list *list);

/**
 * Comparing utils.
 */

_Bool are_equal_aio_values(struct aio_value *value_1, struct aio_value *value_2);

_Bool is_more_aio_value_then_other(struct aio_value *value_1, struct aio_value *value_2);

_Bool is_less_aio_value_then_other(struct aio_value *value_1, struct aio_value *value_2);

_Bool is_more_or_equals_aio_value_then_other(struct aio_value *value_1, struct aio_value *value_2);

_Bool is_less_or_equals_aio_value_then_other(struct aio_value *value_1, struct aio_value *value_2);

/**
 * Casts.
 */

struct aio_value *cast_to_int(struct aio_value *value);

struct aio_value *cast_to_double(struct aio_value *value);

struct aio_value *cast_to_string(struct aio_value *value);

struct aio_value *cast_to_boolean(struct aio_value *value);

struct aio_value *cast_to_reference(struct aio_value *value);

struct aio_value *cast_to_type(struct aio_value *value, const struct str_hook *type);

/**
 * Typedef utils.
 */

typedef const aio_value *const_aio_value;

typedef aio_value **aio_value_array;

typedef const aio_value **const_aio_value_array;

typedef const aio_value_list const_aio_value_list;

#endif //AIO_VALUE_H