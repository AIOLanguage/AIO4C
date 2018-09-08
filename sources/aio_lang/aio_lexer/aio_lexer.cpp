#include <lib4aio_cpp_headers/utils/str_hook/str_hook/str_hook.h>
#include <aio_lang/aio_lexer/aio_lexer.h>

using namespace lib4aio;

/**
 * AIO values.
 */

bool is_aio_true_modifier(const str_hook *hook)
{
    return hook->equals_string(AIO_TRUE_VALUE);
}

bool is_aio_false_modifier(const str_hook *hook)
{
    return hook->equals_string(AIO_FALSE_VALUE);
}

bool is_aio_null_modifier(const str_hook *hook)
{
    return hook->equals_string(AIO_NULL_VALUE);
}