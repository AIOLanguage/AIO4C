#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../headers/lib/collections/sets/string_set.h"
#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"

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

const_boolean is_aio_mutable_modifier(const_string string) {
    return strcmp(string, AIO_MUTABLE_MODIFIER) == 0;
}

const_boolean is_aio_if_modifier(const_string string) {
    return strcmp(string, AIO_IF_MODIFIER) == 0;
}

const_boolean is_aio_loop_modifier(const_string string) {
    return strcmp(string, AIO_LOOP_MODIFIER) == 0;
}

boolean can_use_name(const_string name) {
    for (int i = 0; i < AIO_NUMBER_OF_RESERVED_NAMES; i++) {
        if (strcmp(name, reserved_names[i]) == 0) {
            return false;
        }
    }
    //Check in aio type set:
    return !contains_string_in_set(core->aio_type_set, name);
}