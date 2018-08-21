#include <malloc.h>
#include <mem.h>
#include "../../../../headers/lib/utils/error_utils/error_utils.h"

_Bool matches_int(const char *string)
{
    int start = 0;
    int length = strlen(string);
    if (length == 0) {
        throw_error("empty string as Int!");

    }
    if (string[0] == '-') {
        if (length == 1) {
            throw_error("this is a minus as Int!");
        }
        start = 1;
    }
    for (int i = start; i < strlen(string); ++i) {
        int e = string[i] - '0';
        if (e < 0 || e > 9) {
            return -1;
        }
    }
    return 0;
}

int string_to_int(const char *string)
{
    if (matches_int(string) != 0) {
        throw_error("cannot convert string from int in string_to_int!");
    }
    int result = 0;
    for (int i = 0; i < strlen(string); i++) {
        result = result * 10 + (string[i] - '0');
    }
    return result;
}