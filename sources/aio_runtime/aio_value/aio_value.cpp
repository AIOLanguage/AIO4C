#include <stdlib.h>
#include <aio_lang/aio_types/aio_types.h>
#include <aio_runtime/aio_value/aio_value.h>
#include <lib4aio_cpp_headers/utils/memory_utils/memory_utils.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/string_utils/match.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <lib4aio_cpp_headers/utils/string_utils/suffix_prefix.h>
#include <lib4aio_cpp_headers/utils/string_utils/cast.h>

#define AIO_VALUE_TAG "AIO_VALUE"

#define AIO_VALUE_DEBUG

using namespace lib4aio;

aio_value *new_aio_value(const str_hook *type)
{
    aio_value *value = static_cast<aio_value *>(new_object(sizeof(aio_value *)));
    value->type = type;
    return value;
}

aio_value *new_aio_int_value(const int int_acc)
{
    auto value = new_aio_value(new str_hook(INTEGER));
    value->get.int_acc = int_acc;
    return value;
}

aio_value *new_aio_double_value(const double double_acc)
{
    auto value = new_aio_value(new str_hook(DOUBLE));
    value->get.double_acc = double_acc;
    return value;
}

aio_value *new_aio_string_value(const char *string_acc)
{
    auto value = new_aio_value(new str_hook(STRING));
    value->get.string_acc = new_string(string_acc);
    return value;
}

aio_value *new_aio_boolean_value(const bool boolean_acc)
{
    auto value = new_aio_value(new str_hook(BOOLEAN));
    value->get.boolean_acc = boolean_acc;
    return value;
}

aio_value *new_aio_void_value(void *reference)
{
    auto value = new_aio_value(new str_hook(VOID));
    value->get.reference = reference;
    return value;
}

aio_value *new_aio_type_value(void *reference, const str_hook *type)
{
    auto value = new_aio_value(new str_hook(type));
    value->get.reference = reference;
    return value;
}

aio_value *new_aio_value_by_string(const char *undefined_value)
{
    if (matches_int(undefined_value)) {
        auto int_value = string_to_int(undefined_value);
        return new_aio_int_value(int_value);
    } else if (matches_double(undefined_value)) {
        auto double_value = string_to_double(undefined_value);
        return new_aio_double_value(double_value);
    } else if (matches_string(undefined_value)) {
        static auto SINGLE_QUOTE = "\'";
        auto string_value = remove_prefix_suffix(undefined_value, SINGLE_QUOTE, SINGLE_QUOTE);
        return new_aio_string_value(string_value);
    } else if (matches_boolean(undefined_value)) {
        auto boolean_value = string_to_boolean(undefined_value);
        return new_aio_boolean_value(boolean_value);
    } else {
        throw_error_with_tag(AIO_VALUE_TAG, "Classes are not yet developed in AIO");
    }
}

void free_aio_value(aio_value *value)
{
    if (value) {
        auto type = value->type;
        auto is_string_type = type->equals_string(STRING);
        if (is_string_type) {
            auto string_value = value->get.string_acc;
            value->get.string_acc = nullptr;
            free_string(string_value);
        }
        value->get.reference = nullptr;
        delete type;
        free(value);
    }
}