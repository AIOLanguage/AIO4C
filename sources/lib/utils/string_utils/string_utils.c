#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <assert.h>
#include <stddef.h>

#define TRUE 0
#define FALSE (-1)

//Passed JUnitTest!
int is_white_space(const char c) {
    return c == ' ';
}

//박수!
//Passed JUnitTest!
char **filter(char **src, int src_size, int (*filterFunction)(char *)) {
    int *new_indices = calloc((size_t) src_size, sizeof(int));
    if (new_indices == NULL) {
        perror("cannot allocate memory for *new indices in filter");
        exit(1);
    }
    char **dst;
    size_t new_length = 0;
    //Look at strings and measure new string:
    for (int i = 0; i < src_size; ++i) {
        if (filterFunction(src[i]) == 0) {
            new_indices[i] = i;
            new_length++;
        } else {
            new_indices[i] = -1;
        }
    }
    if (new_length > 0) {
        dst = calloc(new_length, sizeof(char *));
        if (dst == NULL) {
            perror("cannot allocate memory for *dst in filter");
            exit(1);
        }
    } else {
        dst = calloc(1, sizeof(char *));
        if (dst == NULL) {
            perror("cannot allocate memory for *dst in filter");
            exit(1);
        }
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
int is_not_empty_string(char *string) {
    if (strcmp(string, "") != 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

//Passed JUnitTest!
int is_empty_string(char *string) {
    return strcmp(string, "");
}

//준비된!
//Passed JUnitTest!
char *join_to_string(char **src_strings, char *delimiter, const int src_size) {
    char *dst;
    int delimiter_length = strlen(delimiter);
    //Delimiters less than strings by 1:
    int current_string_length = 0 - delimiter_length;
    for (int i = 0; i < src_size; ++i) {
        //Get increase length of general string:
        current_string_length = current_string_length + strlen(src_strings[i]) + delimiter_length;
    }
    if (current_string_length == 0) {
        dst = calloc(2, sizeof(char));
        if (dst == NULL) {
            perror("cannot allocate memory for dst");
        }
        return dst;
    }
    dst = calloc((size_t) current_string_length, sizeof(char));
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
int is_word(char *line) {
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
void concat_string_to_string(char *dst, char *src) {
    strcat(dst, src);
}

//Passed JUnitTest!
void concat_char_to_string(char *dst, char src) {
    int dst_length = strlen(dst);
    dst = realloc(dst, (dst_length + 2) * sizeof(char));
    dst[dst_length] = src;
}