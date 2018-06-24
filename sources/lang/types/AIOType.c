#include <ctype.h>
#include <stdio.h>
#include <mem.h>
#include <comip.h>
#include "../../../headers/lang/types/AIOType.h"

//Passed JUnitTest!
int matchesInt(char *word) {
    int start = 0;
    int length = strlen(word);
    if (length == 0) {
        printf("empty string as Int!");
        exit(1);
    }
    if (word[0] == '-') {
        if (length == 1) {
            printf("this is a minus as Int!");
            exit(1);
        }
        start = 1;
    }
    for (int i = start; i < strlen(word); ++i) {
        int e = word[i] - '0';
        if (e < 0 || e > 9) {
            return -1;
        }
    }
    return 0;
}

//Passed JUnitTest!
int matchesDou(char *word) {
    int result = -1;
    int wasDot = -1;
    int wasFraction = -1;
    int start = 0;
    int length = strlen(word);
    if (length == 0) {
        printf("empty string as Dou!");
        exit(1);
    }
    if (word[0] == '-') {
        if (length == 1) {
            printf("this is a minus as Dou!");
            exit(1);
        }
        start = 1;
    }
    for (int i = start; i < strlen(word); ++i) {
        int e = word[i] - '0';
        if ((e < 0 || e > 9)) {
            if (word[i] == '.' && wasDot == -1) {
                wasDot = 0;
            } else {
                return -1;
            }
        }
        if (e >= 0 && e < 10 && wasDot == 0) {
            wasFraction = 0;
        }
    }
    if (wasDot == 0 && wasFraction == 0) {
        result = 0;
    }
    return result;
}

//Passed JUnitTest!
int matchesCha(char *word) {
    int result = -1;
    int length = strlen(word);
    if (length == 3 && word[0] == '\'' && word[length - 1] == '\'') {
        result = 0;
    }
    return result;
}

//Passed JUnitTest!
int matchesStr(char *word) {
    int result = -1;
    int length = strlen(word);
    if ((length == 2 || length > 3) && word[0] == '\'' && word[length - 1] == '\'') {
        result = 0;
    }
    return result;
}

//끝난!
void setType(char *value, enum AIOType *type) {
    if (matchesInt(value)) {
        *type = AIO_INT;
    } else if (matchesDou(value)) {
        *type = AIO_DOU;
    } else if (matchesCha(value)) {
        *type = AIO_CHA;
    } else if (matchesStr(value)) {
        *type = AIO_STR;
    }
}

//끝난!
int isAIOIntType(enum AIOType type) {
    if (type == AIO_INT) {
        return 0;
    } else {
        return -1;
    }
}

//끝난!
int isAIODouType(enum AIOType type) {
    if (type == AIO_DOU) {
        return 0;
    } else {
        return -1;
    }
}

//끝난!
int isAIOChaType(enum AIOType type) {
    if (type == AIO_CHA) {
        return 0;
    } else {
        return -1;
    }
}

//끝난!
int isAIOStrType(enum AIOType type) {
    if (type == AIO_STR) {
        return 0;
    } else {
        return -1;
    }
}

//끝난!
void str_to_int(char *word, int **dst) {
    *dst = calloc(1, sizeof(int));
    if (*dst == NULL) {
        perror("cannot allocate memory for dst in str_to_int!");
        exit(1);
    }
    if (matchesInt(word) != 0) {
        perror("cannot convert string to int in str_to_int!");
        exit(1);
    }
    **dst = 0;
    for (int i = 0; i < strlen(word); i++) {
        **dst = **dst * 10 + (word[i] - '0');
    }
}

//끝난!
void str_to_dou(char *word, double **dst) {
    *dst = calloc(1, sizeof(double));
    if (*dst == NULL) {
        perror("cannot allocate memory for dst in str_to_dou!");
        exit(1);
    }
    if (matchesDou(word) != 0) {
        perror("cannot convert string to int in str_to_dou!");
        exit(1);
    }
    int integerPart = 0;
    int i = 0;
    while (1) {
        if (word[i] == '.') {
            break;
        } else {
            integerPart = integerPart * 10 + (word[i] - '0');
            i = i + 1;
        }
    }
    double fractionPart = 0.0;
    int fractionCounter = 1;
    for (int j = i + 1; j < strlen(word); ++j) {
        fractionPart = fractionPart + (((double) (word[i] - '0')) / fractionCounter);
        fractionCounter = fractionCounter * 10;
    }
    **dst = ((double) integerPart) + fractionPart;
}


//Passed JUnitTest!
void int_to_str(int src, char **dst) {
    int division = src;
    unsigned intSizeInString = 0;
    while (division != 0) {
        division = division / 10;
        intSizeInString = intSizeInString + 1;
    }
    char *integerArray;
    int negativeShift = 0;
    if (intSizeInString > 0) {
        if (src < 0) {
            negativeShift = 1;
        }
        integerArray = calloc(intSizeInString + 1 + negativeShift, sizeof(char));
        if (integerArray == NULL) {
            perror("cannot allocate memory for integerArray in int_to_str");
            exit(1);
        }
        division = src;
        integerArray[0] = '-';
        int pointer = intSizeInString - 1 + negativeShift;
        while (division != 0) {
            (integerArray)[pointer] = (char) (abs(division % 10) + '0');
            division = division / 10;
            pointer--;
        }
    } else {
        integerArray = calloc(2, sizeof(char));
        if (integerArray == NULL) {
            perror("cannot allocate memory for integerArray in int_to_str");
            exit(1);
        }
        integerArray[0] = '0';
        intSizeInString = 1;
    }
    (*dst) = calloc(intSizeInString + 1 + negativeShift, sizeof(char));
    if (*dst == NULL) {
        perror("cannot allocate memory for dst array!");
        exit(1);
    }
    for (int k = 0; k < intSizeInString + negativeShift; ++k) {
        (*dst)[k] = integerArray[k];
    }
    free(integerArray);
}

//Passed JUnitTest!
void dou_to_str(double src, char **dst) {
    int division = (int) src;
    unsigned intSizeInString = 0;
    while (division != 0) {
        division = division / 10;
        intSizeInString = intSizeInString + 1;
    }
    char *integerArray;
    int negativeShift = 0;
    if (intSizeInString > 0) {
        if (src < 0) {
            negativeShift = 1;
        }
        integerArray = calloc(intSizeInString + 1 + negativeShift, sizeof(char));
        if (integerArray == NULL) {
            perror("cannot allocate memory for integerArray in int_to_str");
            exit(1);
        }
        division = (int) src;
        integerArray[0] = '-';
        int pointer = intSizeInString - 1 + negativeShift;
        while (division != 0) {
            (integerArray)[pointer] = (char) (abs(division % 10) + '0');
            division = division / 10;
            pointer--;
        }
    } else {
        integerArray = calloc(2, sizeof(char));
        if (integerArray == NULL) {
            perror("cannot allocate memory for integerArray in int_to_str");
            exit(1);
        }
        integerArray[0] = '0';
        intSizeInString = 1;
    }
    double fractionalPart;
    if (src < 0) {
        fractionalPart = src * (-1.0) - (int) ((-1) * src);
    } else {
        fractionalPart = src - abs((int) src);
    }
    //Until 1E-9:
    int *fractionalArray = calloc(9, sizeof(int));
    if (fractionalArray == NULL) {
        perror("cannot allocate memory for fractional array!");
        exit(1);
    }
    int fractionalSizeInString = 1;
    for (int i = 0; i < 9; ++i) {
        fractionalPart = fractionalPart * 10;
        fractionalArray[i] = (int) fractionalPart;
        fractionalPart = fractionalPart - (int) fractionalPart;
        fractionalSizeInString = fractionalSizeInString + 1;
    }
    (*dst) = calloc(intSizeInString + fractionalSizeInString + 2 + negativeShift, sizeof(char));
    if (*dst == NULL) {
        perror("cannot allocate memory for dst array!");
        exit(1);
    }
    for (int k = 0; k < intSizeInString + negativeShift; ++k) {
        (*dst)[k] = integerArray[k];
    }
    (*dst)[intSizeInString + negativeShift] = '.';
    for (int j = 0; j < fractionalSizeInString; ++j) {
        (*dst)[intSizeInString + 1 + j + negativeShift] = (char) (fractionalArray[j] + '0');
    }
    free(integerArray);
    free(fractionalArray);
}

void chaToStr(char src, char **dst) {
    *dst = calloc(2, sizeof(char));
    if (*dst == NULL) {
        perror("cannot allocate memory for dst array!");
        exit(1);
    }
    *dst[0] = src;
}