#include <stdio.h>
#include <stdlib.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>

#define ERROR_TAG "AIO_ERROR"

namespace lib4aio {

    void throw_error(const_string message)
    {
        perror(message);
        free((void *) message);
        exit(1);
    }

    void throw_error_with_tag(const_string tag, const_string message)
    {
        printf("\n%s: %s: %s\n", ERROR_TAG, tag, message);
        free((void *) message);
        exit(1);
    }

    void throw_error_with_details(const_string tag, const_string message, const_string value)
    {
        printf("\n%s %s: %s %s\n", ERROR_TAG, tag, message, value);
        free((void *) message);
        exit(1);
    }
}