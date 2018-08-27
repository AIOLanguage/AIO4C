#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../headers/lang/aio_type/aio_type.h"

aio_core *core;

boolean is_aio_type_hooked(const_str_hook *hook)
{
    return contains_string_in_set_by_hook(core->aio_type_set, hook);
}

boolean is_aio_type_initialized(const_str_hook *hook)
{
    return !is_hook_equals_str(hook, AIO_NOT_INIT_TYPE);
}

boolean is_aio_void_type_hooked(const_str_hook *hook)
{
    return is_hook_equals_str(hook, VOID);
}