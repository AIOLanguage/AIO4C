#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"

aio_core *core;

boolean is_aio_type_hooked(const_str_hook *hook) {
    return contains_string_in_set_by_hook(core->aio_type_set, hook);
}