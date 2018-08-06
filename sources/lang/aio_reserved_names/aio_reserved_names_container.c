#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../headers/lib/collections/sets/string_set.h"
#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"

aio_core *core;


char reserved_names[10][4] = {
        {"mu"},
        {"in"},
        {"loo"},
        {"out"},
        {"whe"},
        {"brk"},
};

const_boolean is_aio_mutable_modifier(const_string string) {
    return strcmp(string, AIO_MUTABLE_MODIFIER) == 0;
}

boolean can_use_name(const_string name) {
    for (int i = 0; i < 6; i++) {
        if (strcmp(name, reserved_names[i]) == 0) {
            return false;
        }
    }
    //check in aio_type_set:
    return contains_string_in_set(core->aio_type_set, name);
}