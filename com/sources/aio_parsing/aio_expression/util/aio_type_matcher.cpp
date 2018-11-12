#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <aio_lang/aio_modifiers/aio_modifiers.h>

#define AIO_TYPE_ERROR_TAG "AIO_TYPE_ERROR"

bool is_int_hooked(const str_hook *hook)
{
    const char *string = hook->get_string();
    const unsigned length = hook->get_size();
    int start_position = hook->start;
    if (length <= 0) {
        throw_error_with_tag(AIO_TYPE_ERROR_TAG, "Empty string doesn't matches int!");
    }
    if (string[start_position] == '-') {
        if (length == 1) {
            throw_error_with_tag(AIO_TYPE_ERROR_TAG, "Minus doesn't matches int!");
        }
        start_position++;
    }
    for (int i = start_position; i < hook->end; ++i) {
        const int digit = string[i] - '0';
        if (digit < 0 || digit > 9) {
            return false;
        }
    }
    return true;
}

bool is_double_hooked(const str_hook *hook)
{
    const char *string = hook->get_string();
    const unsigned length = hook->get_size();
    bool was_dot = false;
    bool was_fraction = false;
    int start_position = hook->start;
    if (length <= 0) {
        throw_error_with_tag(AIO_TYPE_ERROR_TAG, "Empty string doesn't matches double!");
    }
    if (string[start_position] == '-') {
        if (length == 1) {
            throw_error_with_tag(AIO_TYPE_ERROR_TAG, "Minus doesn't matches double!");
        }
        start_position++;
    }
    for (int i = start_position; i < hook->end; ++i) {
        const int digit = string[i] - '0';
        if ((digit < 0 || digit > 9)) {
            if (string[i] == '.' && !was_dot) {
                was_dot = true;
            } else {
                return false;
            }
        }
        if (digit >= 0 && digit < 10 && was_dot) {
            was_fraction = true;
        }
    }
    return was_dot && was_fraction;
}

bool is_string_hooked(const str_hook *hook)
{
    const unsigned length = hook->get_size();
    const char *hooked_string = hook->get_string();
    return length > 1 && hooked_string[hook->start] == '\'' && hooked_string[hook->end - 1] == '\'';
}

bool is_boolean_hooked(const str_hook *hook)
{
    return hook->equals_string(AIO_TRUE_VALUE) || hook->equals_string(AIO_FALSE_VALUE);
}