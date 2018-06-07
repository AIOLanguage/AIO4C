#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>
#include <ctype.h>

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

//Passed JUnitTest!
int isWhiteSpace(char c) {
    return c == ' ';
}

//Passed JUnitTest!
int trimStart(const char *src, char **dst) {
    if (strlen(src) == 0) {
        return 0;
    }
    const size_t srcSize = strlen(src);
    int lp = 0;
    while (isWhiteSpace(src[lp]) && ++lp);
    if (lp != 0) {
        (*dst) = (char *) realloc((*dst), sizeof(char) * srcSize - lp);
    }
    int i;
    for (i = lp; i < srcSize; ++i) {
        (*dst)[i - lp] = src[i];
    }
    (*dst)[srcSize - lp] = '\0';
    return lp;
}

//Passed JUnitTest!
int trimEnd(const char *src, char **dst) {
    if (strlen(src) == 0) {
        return 0;
    }
    const size_t srcSize = strlen(src);
    int rp = 0;
    while (isWhiteSpace(src[srcSize - rp - 1]) && ++rp);
    if (rp != 0) {
        (*dst) = (char *) realloc((*dst), sizeof(char) * srcSize - rp);
    }
    int i;
    for (i = 0; i < srcSize - rp; ++i) {
        (*dst)[i] = src[i];
    }
    (*dst)[srcSize - rp] = '\0';
    return rp;
}

//Passed JUnitTest!
int trim(const char *src, char **dst) {
    if (strlen(src) == 0) {
        return 0;
    }
    const size_t srcSize = strlen(src);
    int lp = 0;
    int rp = 0;
    while (isWhiteSpace(src[lp]) && ++lp);
    while (isWhiteSpace(src[srcSize - rp - 1]) && ++rp);
    if (lp + rp != 0) {
        (*dst) = (char *) realloc((*dst), sizeof(char) * srcSize - lp - rp);
    }
    int i;
    for (i = lp; i < srcSize - rp; ++i) {
        (*dst)[i - lp] = src[i];
    }
    (*dst)[srcSize - lp - rp] = '\0';
    return lp + rp;
}

//Passed JUnitTest!
int removePrefix(const char *src, const char *prefix, char **dst) {
    if (strlen(src) == 0) {
        return 0;
    }
    const size_t srcSize = strlen(src);
    int lp = 0;
    for (int j = 0; j < strlen(prefix); ++j) {
        if (src[j] != prefix[j]) {
            return 0;
        } else {
            lp = lp + 1;
        }
    }
    if (lp < srcSize) {
        (*dst) = (char *) realloc((*dst), sizeof(char) * srcSize - lp);
    } else {
        return 0;
    }
    int i;
    for (i = lp; i < srcSize; ++i) {
        (*dst)[i - lp] = src[i];
    }
    (*dst)[srcSize - lp] = '\0';
    return lp;
}

//Passed JUnitTest!
int removeSuffix(const char *src, const char *suffix, char **dst) {
    if (strlen(src) == 0) {
        return 0;
    }
    const size_t srcSize = strlen(src);
    const size_t suffixSize = strlen(suffix);
    int rp = 0;
    for (int j = 0; j < suffixSize; ++j) {
        if (src[srcSize - suffixSize + j] != suffix[j]) {
            return 0;
        } else {
            rp = rp + 1;
        }
    }
    if (rp < srcSize) {
        (*dst) = (char *) realloc((*dst), sizeof(char) * srcSize - rp);
    } else {
        return 0;
    }
    int i;
    for (i = 0; i < srcSize - rp; ++i) {
        (*dst)[i] = src[i];
    }
    (*dst)[srcSize - rp] = '\0';
    return rp;
}

//Passed JUnitTest!
int startsWith(const char *src, char *prefix) {
    for (int i = 0; i < strlen(prefix); ++i) {
        if (src[i] != prefix[i]) {
            return -1;
        }
    }
    return 0;
}

//Passed JUnitTest!
int **filter(char **src, size_t srcSize, char ***dst, int (*filterFunction)(char *)) {
    int *newIndices = calloc(srcSize, sizeof(int));
    int newSize = 0;
    //Look at strings and measure new string:
    for (int i = 0; i < srcSize; ++i) {
        if (filterFunction(src[i]) == 0) {
            newIndices[i] = i;
            newSize = newSize + 1;
        } else {
            newIndices[i] = -1;
        }
    }
    if (newSize > 0) {
        (*dst) = (char **) realloc((*dst), sizeof(char *) * newSize);
    }
    int newPointer = 0;
    for (int j = 0; j < srcSize; ++j) {
        if (newIndices[j] != -1) {
            (*dst)[newPointer] = src[j];
            newPointer = newPointer + 1;
        }
    }
    return 0;
}

//Passed JUnitTest!
int isNotEmpty(char *string) {
    if (strcmp(string, "") != 0) {
        return 0;
    } else {
        return -1;
    }
}

//PassedJUnitTest!
void joinToStringWithoutSpaces(char **srcStrings, char **dst) {
    //Get number of strings:
    int srcSize = _msize(srcStrings) / 4;
    int currentStringLength = 0;
    for (int i = 0; i < srcSize; ++i) {
        //Get increase length of general string:
        currentStringLength = currentStringLength + strlen(srcStrings[i]);
    }
    (*dst) = calloc((size_t) currentStringLength, sizeof(char));
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
int joinToString(char **srcStrings, char *delimiter, char **dst) {
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

int isWord(char *line) {
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
}]