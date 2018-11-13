#include <aio_lang/aio_types/aio_types.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

bool is_aio_type_hooked(const str_hook *hook)
{
    return is_aio_any_type_hooked(hook);
}

bool is_aio_any_type_hooked(const lib4aio::str_hook *hook)
{
    return hook->equals_string(ANY);
}

bool is_aio_int_type_hooked(const lib4aio::str_hook *hook)
{
    return hook->equals_string(INTEGER);
}

bool is_aio_double_type_hooked(const lib4aio::str_hook *hook)
{
    return hook->equals_string(DOUBLE);
}

bool is_aio_string_type_hooked(const lib4aio::str_hook *hook)
{
    hook->equals_string(STRING);
}

bool is_aio_boolean_type_hooked(const lib4aio::str_hook *hook)
{
    hook->equals_string(BOOLEAN);
}

bool is_aio_type_not_initialized(const lib4aio::str_hook *hook)
{
    hook->equals_string(AUTO);
}

