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

//Passed JUnitTest!
int filter(char **src, size_t srcSize, char ***dst, int (*filterFunction)(char *)) {
    int *new_indices = calloc(srcSize, sizeof(int));
    if (*new_indices == NULL) {
        perror("cannot allocate memory for *new indices in filter");
        exit(1);
    }
    size_t new_length = 0;
    //Look at strings and measure new string:
    for (int i = 0; i < srcSize; ++i) {
        if (filterFunction(src[i]) == 0) {
            new_indices[i] = i;
            new_length = new_length + 1;
        } else {
            new_indices[i] = -1;
        }
    }
    if (new_length > 0) {
        *dst = calloc(new_length, sizeof(char *));
        if (*dst == NULL) {
            perror("cannot allocate memory for *dst in filter");
            exit(1);
        }
    }
    int new_pointer = 0;
    for (int j = 0; j < srcSize; ++j) {
        if (new_indices[j] != -1) {
            (*dst)[new_pointer] = src[j];
            new_pointer = new_pointer + 1;
        }
    }
    free(new_indices);
    free(&new_length);
    free(&new_pointer);
    return 0;
}

//Passed JUnitTest!
int is_not_empty_string(char *string) {
    if (strcmp(string, "") != 0) {
        return 0;
    } else {
        return -1;
    }
}

//Passed JUnitTest!
int is_empty_string(char *string) {
    return strcmp(string, "");
}

//PassedJUnitTest!
void join_to_string_without_spaces(char **srcStrings, char **dst) {
    //Get number of strings:
    int srcSize = _msize(srcStrings) / 4;
    int currentStringLength = 0;
    for (int i = 0; i < srcSize; ++i) {
        //Get increase length of general string:
        currentStringLength = currentStringLength + strlen(srcStrings[i]);
    }
    (*dst) = calloc((size_t) currentStringLength + 1, sizeof(char));
    if ((*dst) == NULL) {
        perror("cannot allocate memory for dst");
    }
    int position = 0;
    for (int j = 0; j < srcSize; ++j) {
        for (int i = 0; i < strlen(srcStrings[j]); ++i) {
            (*dst)[position] = srcStrings[j][i];
            position = position + 1;
        }
    }
}

//Passed JUnitTest!
int join_to_string(char **srcStrings, char *delimiter, char **dst) {
    //Get number of strings:
    int srcSize = _msize(srcStrings) / 4;
    int delimiterSize = strlen(delimiter);
    //Delimiters less than strings by 1:
    int currentStringLength = 0 - delimiterSize;
    for (int i = 0; i < srcSize; ++i) {
        //Get increase length of general string:
        currentStringLength = currentStringLength + strlen(srcStrings[i]) + delimiterSize;
    }
    if (currentStringLength <= 0) {
        return -1;
    }
    (*dst) = calloc((size_t) currentStringLength, sizeof(char));
    if ((*dst) == NULL) {
        perror("cannot allocate memory for dst");
    }
    int position = 0;
    for (int j = 0; j < srcSize; ++j) {
        int lineLength = strlen(srcStrings[j]);
        for (int i = 0; i < lineLength; ++i) {
            (*dst)[position] = srcStrings[j][i];
            position = position + 1;
        }
        if (j != srcSize - 1) {
            for (int i = 0; i < delimiterSize; ++i) {
                (*dst)[position] = delimiter[i];
                position = position + 1;
            }
        }
    }
    return 0;
}

int is_word(char *line) {
    int length = strlen(line);
    if (length < 1) {
        return -1;
    }
    if (isalpha(line[0])) {
        if (length > 1) {
            for (int i = 1; i < length; ++i) {
                if (!isalnum(line[i])) {
                    return -1;
                }
            }
        }
    }
    return 0;
}

void substring(const char *string, int offset, int length, char **dst) {
    *dst = calloc((size_t) (length + 1), sizeof(char));
    for (int i = 0; i < length; ++i) {
        (*dst)[i] = string[offset + i];
    }
}

void concat_string_to_string(char *src, char **dst) {
    const size_t oldDstLength = strlen(*dst);
    const size_t newDstLength = oldDstLength + strlen(src) + 1;
    realloc(*dst, newDstLength * sizeof(char));
    if (*dst == NULL) {
        perror("cannot reallocate memory for dst in concat_string_to_string!");
        exit(1);
    }
    for (int i = oldDstLength; i < newDstLength - 1; i++) {
        *dst[i] = src[i - oldDstLength];
    }
    *dst[newDstLength - 1] = '\0';
}

void concat_char_to_string(char src, char **dst) {
    const size_t dstLength = strlen(*dst);
    realloc(*dst, dstLength + 2 * sizeof(char));
    if (*dst == NULL) {
        perror("cannot reallocate memory for dst in concat_char_to_string!");
        exit(1);
    }
    *dst[dstLength] = src;
    *dst[dstLength + 1] = '\0';
}