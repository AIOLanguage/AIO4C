#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <assert.h>

int splitByChar(char *string, char delimiter, char ***dst) {
    size_t length = strlen(string);
    if (length < 1 || delimiter == '\0') {
        *dst = calloc(1, sizeof(char *));
        **dst = calloc(length, sizeof(char));
        strcpy(**dst, string);
        return -1;
    }
    unsigned *indices = calloc(length, sizeof(int));
    if (indices == NULL) {
        perror("cannot allocate memory for indices in split by char!");
    }
    unsigned pointers = 0;
    //Mark split points:
    for (unsigned i = 0; i < length; ++i) {
        if (string[i] == delimiter) {
            indices[pointers] = i;
            pointers++;
        }
    }
    indices = realloc(indices, pointers * sizeof(unsigned));
    printf("POINTERS: %d\n", pointers);
    //Cannot find points:
    if (pointers == 0) {
        *dst = calloc(1, sizeof(char *));
        **dst = calloc(length, sizeof(char));
        strcpy(**dst, string);
        return -1;
    }
    //Parts more than pointers by 1:
    const unsigned parts = pointers + 1;
    *dst = (char **) calloc(parts, sizeof(char *));
    if (*dst == NULL) {
        perror("cannot allocate memory for *dst in split by char!");
    }
    //Create first path:
    if (indices[0] == 0) {
        (*dst)[0] = calloc(1, sizeof(char));
        if ((*dst)[0] == NULL) {
            perror("cannot allocate memory for *dst[0] in split by char!");
        }
        (*dst)[0] = "";
    } else {
        (*dst)[0] = calloc(indices[0], sizeof(char));
        if ((*dst)[0] == NULL) {
            perror("cannot allocate memory for *dst[0] in split by char!");
        }
        for (int i = 0; i < indices[0]; ++i) {
            (*dst)[0][i] = string[i];
        }
    }
    printf("FIRST: -%s-\n", *dst[0]);
    //Create last part:
    const int last = parts - 1;
    if (length - indices[pointers - 1] == 0) {
        (*dst)[last] = calloc(1, sizeof(char));
        if ((*dst)[last] == NULL) {
            perror("cannot allocate memory for *dst[last] in split by char!");
        }
        (*dst)[last] = "";
    } else {
        (*dst)[last] = calloc(length - indices[pointers - 1] - 1, sizeof(char));
        if ((*dst)[last] == NULL) {
            perror("cannot allocate memory for *dst[last] in split by char!");
        }
        int k = 0;
        for (int i = indices[pointers - 1] + 1; i < length; ++i) {
            (*dst)[last][k] = string[i];
            k = k + 1;
        }
    }
    printf("LAST: -%s-\n", (*dst)[last]);
    if (pointers > 1) {
        //from second delimiter:
        for (int j = 0; j < pointers - 1; ++j) {
            printf("DISTANCE: %d\n", indices[j + 1] - indices[j] - 1);
            if (indices[j + 1] - indices[j] - 1 > 0) {
                (*dst)[j + 1] = calloc(indices[j + 1] - indices[j], sizeof(char));
                if ((*dst)[j + 1] == NULL) {
                    perror("cannot allocate memory for *dst[j] in split by char!");
                }
                printf("\n\n\n\n\n\n\n");
                for (int i = 0; i < indices[j + 1] - indices[j] - 1; ++i) {
                    printf("SRC_CHAR: %c\n", string[indices[j] + i + 1]);
                    (*dst)[j + 1][i] = string[indices[j] + i + 1];
                }
                printf("IN THE MIDDLE: -%s-\n", (*dst)[j]);
            } else {
                (*dst)[j + 1] = calloc(1, sizeof(char));
                if ((*dst)[j + 1] == NULL) {
                    perror("cannot allocate memory for *dst[j] in split by char!");
                }
                (*dst)[j + 1] = "";
            }
        }
    }
    return 0;
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
}