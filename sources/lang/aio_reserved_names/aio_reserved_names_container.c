#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../headers/lib/utils/str_hook/str_hook.h"
#include "../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"

aio_core *core;

#define AIO_NUMBER_OF_RESERVED_NAMES 7

char reserved_names[AIO_NUMBER_OF_RESERVED_NAMES][4] = {
        {AIO_BREAK_MODIFIER},
        {AIO_IF_MODIFIER},
        {AIO_IN_MODIFIER},
        {AIO_LOOP_MODIFIER},
        {AIO_MUTABLE_MODIFIER},
        {AIO_RETURN_MODIFIER},
        {AIO_SWITCH_MODIFIER},
};

boolean is_aio_mutable_modifier(const_str_hook *hook) {
    return is_hooked_str_equals_str(hook, AIO_MUTABLE_MODIFIER);
}

boolean is_aio_if_modifier(const_str_hook *hook) {
    return is_hooked_str_equals_str(hook, AIO_IF_MODIFIER);
}

boolean is_aio_loop_modifier(const_str_hook *hook) {
    return is_hooked_str_equals_str(hook, AIO_LOOP_MODIFIER);
}

boolean can_use_name(const_str_hook *hook) {
    for (int i = 0; i < AIO_NUMBER_OF_RESERVED_NAMES; i++) {
        if (is_hooked_str_equals_str(hook, reserved_names[i])) {
            return FALSE;
        }
    }
    //Check in aio type set:
    const_boolean is_valid_name = !contains_string_in_set_by_hook(core->aio_type_set, hook);
    return is_valid_name;
}