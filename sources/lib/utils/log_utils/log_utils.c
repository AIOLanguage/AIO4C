#include <malloc.h>
#include <stdio.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"

void log_info(const_string tag, char *message)
{
    printf("\n%s: %s\n", tag, message);
    //free(message);
}

void log_info_string(const_string tag, char *message, const_string value)
{
    printf("\n%s: %s -%s-\n", tag, message, value);
    //free(message);
}

void log_info_char(const_string tag, char *message, const char value)
{
    printf("\n%s: %s -%c-\n", tag, message, value);
    //free((void *) message);
}

void log_info_double(const_string tag, char *message, const double value)
{
    printf("\n%s: %s -%lf-\n", tag, message, value);
    //free((void *) message);
}

void log_info_int(const_string tag, char *message, const int value)
{
    printf("\n%s: %s -%d-\n", tag, message, value);
    //free((void *) message);
}

void log_info_boolean(const_string tag, char *message, const _Bool value)
{
    const_string boolean_string = NULL;
    if (value) {
        boolean_string = AIO_TRUE;
    } else {
        boolean_string = AIO_FALSE;
    }
    printf("\n%s: %s -%s-\n", tag, message, boolean_string);
    //free((void *) boolean_string);
    //free((void *) message);
}