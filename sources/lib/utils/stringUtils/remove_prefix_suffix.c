#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <assert.h>
#include <stddef.h>

#define TRUE 0
#define FALSE (-1)

int
is_correct_src_prefix(const size_t src_length, const size_t prefix_length, const size_t suffix_length, const char *src,
                      char **dst) {
    if (src_length == 0) {
        *dst = calloc(2, sizeof(char));
        return FALSE;
    }
    if (prefix_length + suffix_length > src_length || (prefix_length == 0 && suffix_length == 0)) {
        *dst = calloc(src_length + 1, sizeof(char));
        strcpy(*dst, src);
        return FALSE;
    }
    return TRUE;
}

int remove_prefix_suffix(const char *src, const char *prefix, const char *suffix, char **dst) {
    const size_t src_length = strlen(src);
    const size_t prefix_length = strlen(prefix);
    const size_t suffix_length = strlen(suffix);
    if (is_correct_src_prefix(src_length, prefix_length, suffix_length, src, dst) == FALSE) {
        return FALSE;
    }
    int left_part = 0;
    for (int j = 0; j < prefix_length; ++j) {
        if (src[j] != prefix[j]) {
            left_part = 0;
            break;
        } else {
            left_part++;
        }
    }
    int right_part = 0;
    for (int j = 0; j < suffix_length; ++j) {
        if (src[src_length - suffix_length + j] != suffix[j]) {
            right_part = 0;
            break;
        } else {
            right_part++;
        }
    }
    size_t num_of_elements = src_length - left_part - right_part;
    *dst = calloc(num_of_elements + 1, sizeof(char));
    for (int i = left_part; i < src_length - right_part; ++i) {
        (*dst)[i - left_part] = src[i];
    }
    return left_part;
}

//Passed JUnitTest!
int remove_prefix(const char *src, const char *prefix, char **dst) {
    return remove_prefix_suffix(src, prefix, "", dst);
}

//Passed JUnitTest!
int remove_suffix(const char *src, const char *suffix, char **dst) {
    return remove_prefix_suffix(src, "", suffix, dst);
}