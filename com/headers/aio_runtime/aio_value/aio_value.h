#ifndef AIO_VALUE_H
#define AIO_VALUE_H

namespace lib4aio {

    class str_hook;
}

using namespace lib4aio;

struct aio_value {

    const str_hook *type;

    union {
        int int_acc;
        double double_acc;
        char *string_acc;
        bool boolean_acc;
        void *reference;
    } get;

    enum {
        AIO_VALUE_SINGLE_DATA, AIO_VALUE_ARRAY_DATA
    } data_type;
};

aio_value *new_aio_value(const str_hook *type);

aio_value *new_aio_value_by_string(const char *undefined_value);

aio_value *new_aio_int_value(const int int_acc);

aio_value *new_aio_double_value(const double double_acc);

aio_value *new_aio_string_value(const char *string_acc);

aio_value *new_aio_boolean_value(const bool boolean_acc);

aio_value *new_aio_void_value(void *value);

aio_value *new_aio_type_value(void *reference, const str_hook *type);

void free_aio_value(aio_value *value);

#endif //AIO_VALUE_H