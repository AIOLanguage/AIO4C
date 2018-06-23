#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <assert.h>
#include <stddef.h>
#include "../../../../headers/lib/utils/stringUtils/string_utils.h"

#define TRUE 0
#define FALSE (-1)

int border_trim(const char *src, char **dst, const int has_left, const int has_right) {
    const size_t src_length = strlen(src);
    if (src_length == TRUE) {
        *dst = calloc(2, sizeof(char));
        return TRUE;
    }
    int left_border = 0;
    int right_border = 0;
    if (has_left == 0) {
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
    *dst = calloc(number_of_elements + 1, sizeof(char));
    if (*dst == NULL) {
        perror("cannot allocate memory for dst in trim_start!");
        exit(1);
    }
    int i;
    for (i = left_border; i < src_length - right_border; ++i) {
        (*dst)[i - left_border] = src[i];
    }
    (*dst)[src_length - left_border] = '\0';
    return left_border + right_border;
}

//Passed JUnitTest!
int trim_start(const char *src, char **dst) {
    return border_trim(src, dst, TRUE, FALSE);
}

//Passed JUnitTest!
int trim_end(const char *src, char **dst) {
    return border_trim(src, dst, FALSE, TRUE);
}

//Passed JUnitTest!
int trim(const char *src, char **dst) {
    return border_trim(src, dst, TRUE, TRUE);
}

void trim_all(char **strings, int number_of_strings, char ***dst) {
    *dst = calloc((size_t) number_of_strings, sizeof(char *));
    if (*dst == NULL) {
        perror("cannot allocate memory for dst when trim all is occurs!");
        exit(1);
    }
    for (int i = 0; i < number_of_strings; ++i) {
        char *trimLine;
        trim(strings[i], &trimLine);
        (*dst)[i] = trimLine;
    }
}