#include <aio_runtime/aio_value/aio_value.h>
#include <aio_runtime/aio_result/aio_result.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

aio_result::aio_result(aio_value *value, str_hook *rest)
{
    this->value = value;
    this->rest = rest;
}

aio_result::aio_result(const int int_acc, str_hook *rest)
{
    this->value = new_aio_int_value(int_acc);
    this->rest = rest;
}

aio_result::aio_result(const double double_acc, str_hook *rest)
{
    this->value = new_aio_double_value(double_acc);
    this->rest = rest;
}

aio_result::aio_result(char *string_acc, str_hook *rest)
{
    this->value = new_aio_string_value(string_acc);
    this->rest = rest;
}

aio_result::aio_result(const bool boolean_acc, str_hook *rest)
{
    this->value = new_aio_boolean_value(boolean_acc);
    this->rest = rest;
}

aio_result::~aio_result()
{
//    const str_hook *old_rest = this->rest;
//    const aio_value *old_value = this->value;
//    this->rest = nullptr;
//    this->value = nullptr;
    delete this->rest;
    delete this->value;
}