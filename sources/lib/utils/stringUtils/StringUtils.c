#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>

char **split(char *string, char delimiter) {
    char **result = 0;
    size_t count = 0;
    char *tmp = string;
    char *lastComma = 0;
    char delim[2];
    delim[0] = delimiter;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp) {
        if (delimiter == *tmp) {
            count++;
            lastComma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += lastComma < (string + strlen(string) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char *) * count);

    if (result) {
        size_t idx = 0;
        char *token = strtok(string, delim);

        while (token) {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

int isWhiteSpace(char c) {
    return c == ' ';
}

int trimStart(const char *src, char **dst) {
    if (strlen(src) == 0) {
        return 0;
    }
    const size_t srcSize = strlen(src);
    int lp /* left padding */ = 0;
    while (isWhiteSpace(src[lp]) && ++lp);
    if (lp != 0) {
        (*dst) = (char *) realloc((*dst), sizeof(char) * srcSize - lp);
    }
    int i;
    for (i = lp; i < srcSize; ++i)
        (*dst)[i - lp] = src[i];

    (*dst)[srcSize - lp] = '\0';
    return lp;
}

int trimEnd(const char *src, char **dst) {
    if (strlen(src) == 0) {
        return 0;
    }
    const size_t srcSize = strlen(src);
    int rp /* right padding */ = 0;
    while (isWhiteSpace(src[srcSize - rp - 1]) && ++rp);
    if (rp != 0) {
        (*dst) = (char *) realloc((*dst), sizeof(char) * srcSize - rp);
    }
    int i;
    for (i = 0; i < srcSize - rp; ++i)
        (*dst)[i] = src[i];

    (*dst)[srcSize - rp] = '\0';
    return rp;
}

int trim(const char *src, char **dst) {
    if (strlen(src) == 0) {
        return 0;
    }
    const size_t srcSize = strlen(src);
    int lp /* left padding */ = 0;
    int rp /* right padding */ = 0;
    while (isWhiteSpace(src[lp]) && ++lp);
    while (isWhiteSpace(src[srcSize - rp - 1]) && ++rp);
    if (lp + rp != 0) {
        (*dst) = (char *) realloc((*dst), sizeof(char) * srcSize - lp - rp);
    }
    int i;
    for (i = lp; i < srcSize - rp; ++i)
        (*dst)[i - lp] = src[i];

    (*dst)[srcSize - lp - rp] = '\0';
    return lp + rp;
}