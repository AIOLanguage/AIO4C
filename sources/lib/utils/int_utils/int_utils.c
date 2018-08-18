#include <malloc.h>
#include <mem.h>
#include <math.h>
#include "../../../../headers/lib/utils/error_utils/error_utils.h"

//Passed JUnitTest!
boolean matches_int(const_string word) {
    int start = 0;
    int length = strlen(word);
    if (length == 0) {
        throw_error("empty string as Int!");

    }
    if (word[0] == '-') {
        if (length == 1) {
            throw_error("this is a minus as Int!");
        }
        start = 1;
    }
    for (int i = start; i < strlen(word); ++i) {
        int e = word[i] - '0';
        if (e < 0 || e > 9) {
            return -1;
        }
    }
    return 0;
}

//끝난!
int string_to_int(const_string word) {
    if (matches_int(word) != 0) {
        throw_error("cannot convert string from int in string_to_int!");
    }
    int result = 0;
    for (int i = 0; i < strlen(word); i++) {
        result = result * 10 + (word[i] - '0');
    }
    return result;
}