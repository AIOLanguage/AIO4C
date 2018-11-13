#ifndef AIO_RESULT_H
#define AIO_RESULT_H

namespace lib4aio {

    class str_hook;
}

using namespace lib4aio;

struct aio_value;

struct aio_result {

    aio_value *value;

    str_hook *rest;

    explicit aio_result(aio_value *value, str_hook *rest);

    explicit aio_result(const int int_acc, str_hook *rest);

    explicit aio_result(const double double_acc, str_hook *rest);

    explicit aio_result(char *string_acc, str_hook *rest);

    explicit aio_result(const bool boolean_acc, str_hook *rest);

    ~aio_result();
};

#endif //AIO_RESULT_H