#include <lib/utils/collections/sets/string_set.h>
#include <lib/utils/boolean_utils/boolean_utils.h>
#include <lib/utils/str_hook/str_hook.h>
#include <aio_core/aio_core.h>
#include <lib/utils/type_utils/type.utils.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <aio_lang/aio_type/aio_type.h>

aio_core *core;

boolean is_aio_type_hooked(const str_hook *hook)
{
    var supported_type_set = core->aio_type_set;
    return contains_string_in_set_by_hook(supported_type_set, hook);
}

boolean is_aio_type_initialized(const str_hook *hook)
{
    return !is_hook_equals_str(hook, AIO_NOT_INIT_TYPE);
}

boolean is_aio_void_type_hooked(const str_hook *hook)
{
    return is_hook_equals_str(hook, VOID);
}

boolean is_aio_int_type_hooked(const str_hook *hook)
{
    return is_hook_equals_str(hook, INTEGER);
}

boolean is_aio_double_type_hooked(const str_hook *hook)
{
    return is_hook_equals_str(hook, DOUBLE);
}

boolean is_aio_string_type_hooked(const str_hook *hook)
{
    return is_hook_equals_str(hook, STRING);
}

boolean is_aio_boolean_type_hooked(const str_hook *hook)
{
    return is_hook_equals_str(hook, BOOLEAN);
}