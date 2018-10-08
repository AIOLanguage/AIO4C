#ifndef LIB4AIO_COMPARE_AIO_VALUE_H
#define LIB4AIO_COMPARE_AIO_VALUE_H

bool are_equal_aio_values(
        const struct aio_value *value_1,
        const struct aio_value *value_2
);

bool are_not_equal_aio_values(
        const struct aio_value *value_1,
        const struct aio_value *value_2
);

bool is_more_aio_value_then_other(
        const struct aio_value *value_1,
        const struct aio_value *value_2
);

bool is_less_aio_value_then_other(
        const struct aio_value *value_1,
        const struct aio_value *value_2
);

bool is_more_or_equals_aio_value_then_other(
        const struct aio_value *value_1,
        const struct aio_value *value_2
);

bool is_less_or_equals_aio_value_then_other(
        const struct aio_value *value_1,
        const struct aio_value *value_2
);

#endif //LIB4AIO_COMPARE_AIO_VALUE_H