#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <assert.h>
#include <stddef.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"

#define TRUE 0
#define FALSE (-1)

//Passed JUnitTest!
boolean is_white_space(char c) {
    return c == ' ';
}

//박수!
//Passed JUnitTest!
string_array filter(string_array src, int src_size, const_boolean (*filter_function)(const_string)) {
    int *new_indices = calloc((size_t) src_size, sizeof(int));
    char **dst;
    size_t new_length = 0;
    //Look at values and measure new string:
    for (int i = 0; i < src_size; ++i) {
        if (filter_function(src[i]) == 0) {
            new_indices[i] = i;
            new_length++;
        } else {
            new_indices[i] = -1;
        }
    }
    if (new_length > 0) {
        dst = calloc(new_length, sizeof(char *));
    } else {
        dst = calloc(1, sizeof(char *));
        return dst;
    }
    int new_pointer = 0;
    for (int j = 0; j < src_size; ++j) {
        if (new_indices[j] != -1) {
            dst[new_pointer] = calloc(strlen(src[j]), sizeof(char));
            dst[new_pointer] = src[j];
            new_pointer++;
        }
    }
    return dst;
}

//Passed JUnitTest!
const_boolean is_not_empty_string(const_string string) {
    if (strcmp(string, "") != 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

//Passed JUnitTest!
const_boolean is_empty_string(const_string string) {
    return strcmp(string, "") == 0;
}

//준비된!
//Passed JUnitTest!
const_string join_to_string(const_string_array src_strings, const_string delimiter, const int src_size) {
    char *dst;
    int delimiter_length = strlen(delimiter);
    //Delimiters less than values by 1:
    int current_string_length = 0 - delimiter_length;
    for (int i = 0; i < src_size; ++i) {
        //Get increase length of general string:
        current_string_length = current_string_length + strlen(src_strings[i]) + delimiter_length;
    }
    if (current_string_length == 0) {
        dst = calloc(2, sizeof(char));
        return dst;
    }
    dst = calloc((size_t) (current_string_length + 1), sizeof(char));
    if (dst == NULL) {
        perror("cannot allocate memory for dst");
    }
    int position = 0;
    for (int j = 0; j < src_size; ++j) {
        int line_length = strlen(src_strings[j]);
        for (int i = 0; i < line_length; ++i) {
            dst[position] = src_strings[j][i];
            position = position + 1;
        }
        if (j != src_size - 1) {
            for (int i = 0; i < delimiter_length; ++i) {
                dst[position] = delimiter[i];
                position = position + 1;
            }
        }
    }
    return dst;
}

//Passed JUnitTest!
const_boolean is_word(const_string line) {
    int length = strlen(line);
    if (length < 1) {
        return FALSE;
    }
    if (isalpha(line[0])) {
        if (length > 1) {
            for (int i = 1; i < length; ++i) {
                if (!isalnum(line[i])) {
                    return FALSE;
                }
            }
        }
    }
    return TRUE;
}

//Passed JUnitTest!
char *substring(const char *string, int offset, int length) {
    char *dst = calloc((size_t) (length + 1), sizeof(char));
    for (int i = 0; i < length; ++i) {
        dst[i] = string[offset + i];
    }
    return dst;
}

//Passed JUnitTest!
void concat_string_to_string(string dst, const_string src) {
    strcat(dst, src);
}

//Passed JUnitTest!
void concat_char_to_string(char **dst, char src) {
    int dst_length = strlen(*dst);
    *dst = realloc(*dst, (dst_length + 2) * sizeof(char));
    *dst[dst_length] = src;
}

int strings_size(const_string_array src) {
    return _msize(src) / 4;
}

void delete_strings(const_string_array src) {
    for (int i = 0; i < strings_size(src); ++i) {
        free((void *) src[i]);
    }
    free(src);
}

string squeeze_string(const_string src) {
    const unsigned src_length = strlen(src);
    string dst = calloc(src_length + 1, sizeof(char));
    int position = 0;
    for (int i = 0; i < src_length; ++i) {
        const char symbol = src[i];
        if (!is_white_space(symbol)) {
            dst[position++] = symbol;
        }
    }
    dst = realloc(dst, position * sizeof(char));
    return dst;
}