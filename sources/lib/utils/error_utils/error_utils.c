#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"

void throw_error(const_string message) {
    perror(message);
    exit(1);
}