#include <mem.h>
#include "../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"

boolean matches_boolean(const_string string)
{
    if (strcmp(string, AIO_TRUE) == 0 || strcmp(string, AIO_FALSE) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

boolean string_to_boolean(const_string string)
{
    if (strcmp(string, AIO_TRUE) == 0) {
        return TRUE;
    }
    if (strcmp(string, AIO_TRUE) == 0) {
        return FALSE;
    }
    throw_error("can not recognize boolean value!");
}