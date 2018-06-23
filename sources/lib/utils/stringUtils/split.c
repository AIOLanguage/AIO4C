#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <assert.h>
#include <stddef.h>

#define TRUE 0
#define FALSE (-1)

void move_empty_string_to_dst(const char *src, char ***dst);

void move_string_to_dst(const char *src, size_t string_length, char ***dst);

void create_left_part(const char *src, const unsigned *indices, char ***dst);

void create_right_part(const char *src, const unsigned *indices, char ***dst, int pointers, size_t length);

//Passed JUnitTests!
int split_by_char(const char *src, const char delimiter, char ***dst) {
    const size_t length = strlen(src);
    //Is empty string:
    if (length < 1 || delimiter == '\0') {
        move_empty_string_to_dst(src, dst);
        return FALSE;
    }
    //Create split indices:
    unsigned *indices = calloc(length, sizeof(int));
    if (indices == NULL) {
        perror("cannot allocate memory for indices in split by char!");
        exit(1);
    }
    unsigned pointers = 0;
    //Mark split points:
    for (unsigned i = 0; i < length; ++i) {
        if (src[i] == delimiter) {
            indices[pointers] = i;
            pointers++;
        }
    }
    //Cannot find points:
    if (pointers == 0) {
        move_string_to_dst(src, length, dst);
        return FALSE;
    }
    indices = realloc(indices, pointers * sizeof(unsigned));
    if (indices == NULL) {
        perror("cannot allocate memory for indices in split by char!");
        exit(1);
    }
    //Parts more than pointers by 1:
    const unsigned parts = pointers + 1;
    *dst = (char **) calloc(parts, sizeof(char *));
    if (*dst == NULL) {
        perror("cannot allocate memory for *dst in split by char!");
        exit(1);
    }
    //Create left part:
    create_left_part(src, indices, dst);
    //Create right part:
    create_right_part(src, indices, dst, pointers, length);
    //Create middle parts:
    if (pointers > 1) {
        //From second delimiter:
        for (int j = 0; j < pointers - 1; ++j) {
            if (indices[j + 1] - indices[j] - 1 > 0) {
                (*dst)[j + 1] = calloc(indices[j + 1] - indices[j] + 1, sizeof(char));
                if ((*dst)[j + 1] == NULL) {
                    perror("cannot allocate memory for *dst[j] in split by char!");
                    exit(1);
                }
                for (int i = 0; i < indices[j + 1] - indices[j] - 1; ++i) {
                    (*dst)[j + 1][i] = src[indices[j] + i + 1];
                }
            } else {
                (*dst)[j + 1] = calloc(2, sizeof(char));
                if ((*dst)[j + 1] == NULL) {
                    perror("cannot allocate memory for *dst[j] in split by char!");
                    exit(1);
                }
                (*dst)[j + 1] = "";
            }
        }
    }
    return TRUE;
}

void move_empty_string_to_dst(const char *src, char ***dst) {
    move_string_to_dst(src, 1, dst);
}

void move_string_to_dst(const char *src, const size_t string_length, char ***dst) {
    //allocate memory for string array:
    *dst = calloc(1, sizeof(char *));
    if (*dst == NULL) {
        perror("cannot allocate memory for *dst in split by char!");
        exit(1);
    }
    //allocate memory for only string:
    **dst = calloc(string_length, sizeof(char));
    if (**dst == NULL) {
        perror("cannot allocate memory for **dst in split by char!");
        exit(1);
    }
    strcpy(**dst, src);
}

void create_left_part(const char *src, const unsigned *indices, char ***dst) {
    (*dst)[0] = calloc(indices[0] + 1, sizeof(char));
    if ((*dst)[0] == NULL) {
        perror("cannot allocate memory for *dst[0] in split by char!");
        exit(1);
    }
    for (int i = 0; i < indices[0]; ++i) {
        (*dst)[0][i] = src[i];
    }
}

void create_right_part(const char *src, const unsigned *indices, char ***dst, int pointers, size_t length) {
    (*dst)[pointers] = calloc(length - indices[pointers - 1] + 1, sizeof(char));
    if ((*dst)[pointers] == NULL) {
        perror("cannot allocate memory for *dst[last] in split by char!");
        exit(1);
    }
    int k = 0;
    for (int i = indices[pointers - 1] + 1; i < length; ++i) {
        (*dst)[pointers][k] = src[i];
        k = k + 1;
    }
}