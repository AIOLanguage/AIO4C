#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <assert.h>
#include <stddef.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"

//Passed JUnitTest!
char *border_trim(const char *src, const int has_left, const int has_right) {
    char *dst;
    const size_t src_length = strlen(src);
    if (src_length == TRUE) {
        dst = calloc(2, sizeof(char));
        if (dst == NULL) {
            perror("cannot allocate memory for dst in trim_start!");
            exit(1);
        }
        return TRUE;
    }
    int left_border = 0;
    int right_border = 0;
    if (has_left == TRUE) {
        while (is_white_space(src[left_border])) {
            left_border++;
        }
    }
    if (has_right == TRUE) {
        while (is_white_space(src[src_length - right_border - 1])) {
            right_border++;
        }
    }
    size_t number_of_elements;
    if (left_border < src_length - 1) {
        number_of_elements = src_length - left_border - right_border + 1;
    } else {
        number_of_elements = 2;
    }
    dst = calloc(number_of_elements + 1, sizeof(char));
    if (dst == NULL) {
        perror("cannot allocate memory for dst in trim_start!");
        exit(1);
    }
    int i;
    for (i = left_border; i < src_length - right_border; ++i) {
        dst[i - left_border] = src[i];
    }
    dst[src_length - left_border] = '\0';
    return dst;
}

//끝난!
//Passed JUnitTest!
char *trim_start(const char *src) {
    return border_trim(src, TRUE, FALSE);
}

//끝난!
//Passed JUnitTest!
char *trim_end(const char *src) {
    return border_trim(src, FALSE, TRUE);
}

//끝난!
//Passed JUnitTest!
char *trim(const char *src) {
    return border_trim(src, TRUE, TRUE);
}

//끝난!
//PassedJUnit Test!
string_array trim_all(const_string_array strings, int number_of_strings) {
    char **dst;
    dst = calloc((size_t) number_of_strings, sizeof(char *));
    for (int i = 0; i < number_of_strings; ++i) {
        dst[i] = trim(strings[i]);
    }
    return dst;
}