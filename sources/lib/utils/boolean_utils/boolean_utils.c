#include <mem.h>
#include "../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"

const_boolean matches_boolean(const_string string) {
    if (strcmp(string, TRUE_STRING) == 0 || strcmp(string, FALSE_STRING) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

const_boolean string_to_boolean(const_string string) {
    if (strcmp(string, TRUE_STRING) == 0) {
        return TRUE;
    }
    if (strcmp(string, FALSE_STRING) == 0) {
        return FALSE;
    }
    throw_error("can not recognize boolean aio_value!");
}