#include <mem.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"

boolean matches_boolean(const_string string)
{
    if (strcmp(string, AIO_TRUE_VALUE) == 0 || strcmp(string, AIO_FALSE_VALUE) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

boolean string_to_boolean(const_string string)
{
    if (strcmp(string, AIO_TRUE_VALUE) == 0) {
        return TRUE;
    }
    if (strcmp(string, AIO_TRUE_VALUE) == 0) {
        return FALSE;
    }
    throw_error("Сan not recognize boolean value!");
}