#include <ctype.h>
#include <stdio.h>
#include <mem.h>
#include <comip.h>
#include "../../../headers/lang/aio_types/aio_type.h"

//Passed JUnitTest!
int matches_int(char *word) {
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
int matches_dou(char *word) {
    int result = -1;
    int was_dot = -1;
    int was_fraction = -1;
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
            if (word[i] == '.' && was_dot == -1) {
                was_dot = 0;
            } else {
                return -1;
            }
        }
        if (e >= 0 && e < 10 && was_dot == 0) {
            was_fraction = 0;
        }
    }
    if (was_dot == 0 && was_fraction == 0) {
        result = 0;
    }
    return result;
}

//Passed JUnitTest!
int matches_cha(char *word) {
    int result = -1;
    int length = strlen(word);
    if (length == 3 && word[0] == '\'' && word[length - 1] == '\'') {
        result = 0;
    }
    return result;
}

//Passed JUnitTest!
int matches_str(char *word) {
    int result = -1;
    int length = strlen(word);
    if ((length == 2 || length > 3) && word[0] == '\'' && word[length - 1] == '\'') {
        result = 0;
    }
    return result;
}

//끝난!
int str_to_int(char *word) {
    if (matches_int(word) != 0) {
        perror("cannot convert string to int in string_to_int!");
        exit(1);
    }
    int result = 0;
    for (int i = 0; i < strlen(word); i++) {
        result = result * 10 + (word[i] - '0');
    }
    return result;
}

//끝난!
double str_to_dou(char *word) {
    if (matches_dou(word) != 0) {
        perror("cannot convert string to int in str_to_dou!");
        exit(1);
    }
    int integer_part = 0;
    int i = 0;
    while (1) {
        if (word[i] == '.') {
            break;
        } else {
            integer_part = integer_part * 10 + (word[i] - '0');
            i = i + 1;
        }
    }
    double fraction_part = 0.0;
    int fraction_counter = 1;
    for (int j = i + 1; j < strlen(word); ++j) {
        fraction_part = fraction_part + (((double) (word[i] - '0')) / fraction_counter);
        fraction_counter = fraction_counter * 10;
    }
    return ((double) integer_part) + fraction_part;
}


//Passed JUnitTest!
char *int_to_str(int src) {
    int division = src;
    unsigned int_size_in_string = 0;
    while (division != 0) {
        division = division / 10;
        int_size_in_string = int_size_in_string + 1;
    }
    char *integer_array;
    int negative_shift = 0;
    if (int_size_in_string > 0) {
        if (src < 0) {
            negative_shift = 1;
        }
        integer_array = calloc(int_size_in_string + 1 + negative_shift, sizeof(char));
        if (integer_array == NULL) {
            perror("cannot allocate memory for integer_array in int_to_str");
            exit(1);
        }
        division = src;
        integer_array[0] = '-';
        int pointer = int_size_in_string - 1 + negative_shift;
        while (division != 0) {
            (integer_array)[pointer] = (char) (abs(division % 10) + '0');
            division = division / 10;
            pointer--;
        }
    } else {
        integer_array = calloc(2, sizeof(char));
        if (integer_array == NULL) {
            perror("cannot allocate memory for integer_array in int_to_str");
            exit(1);
        }
        integer_array[0] = '0';
        int_size_in_string = 1;
    }
    char *dst = calloc(int_size_in_string + 1 + negative_shift, sizeof(char));
    if (dst == NULL) {
        perror("cannot allocate memory for dst array!");
        exit(1);
    }
    for (int k = 0; k < int_size_in_string + negative_shift; ++k) {
        dst[k] = integer_array[k];
    }
    free(integer_array);
    return dst;
}

//Passed JUnitTest!
char *double_to_str(double src) {
    int division = (int) src;
    unsigned int_size_in_string = 0;
    while (division != 0) {
        division = division / 10;
        int_size_in_string = int_size_in_string + 1;
    }
    char *integer_array;
    int negative_shift = 0;
    if (int_size_in_string > 0) {
        if (src < 0) {
            negative_shift = 1;
        }
        integer_array = calloc(int_size_in_string + 1 + negative_shift, sizeof(char));
        if (integer_array == NULL) {
            perror("cannot allocate memory for integer_array in int_to_str");
            exit(1);
        }
        division = (int) src;
        integer_array[0] = '-';
        int pointer = int_size_in_string - 1 + negative_shift;
        while (division != 0) {
            (integer_array)[pointer] = (char) (abs(division % 10) + '0');
            division = division / 10;
            pointer--;
        }
    } else {
        integer_array = calloc(2, sizeof(char));
        if (integer_array == NULL) {
            perror("cannot allocate memory for integer_array in int_to_str");
            exit(1);
        }
        integer_array[0] = '0';
        int_size_in_string = 1;
    }
    double fractional_part;
    if (src < 0) {
        fractional_part = src * (-1.0) - (int) ((-1) * src);
    } else {
        fractional_part = src - abs((int) src);
    }
    //Until 1E-9:
    int *fractional_array = calloc(9, sizeof(int));
    if (fractional_array == NULL) {
        perror("cannot allocate memory for fractional array!");
        exit(1);
    }
    int fractional_size_in_string = 1;
    for (int i = 0; i < 9; ++i) {
        fractional_part = fractional_part * 10;
        fractional_array[i] = (int) fractional_part;
        fractional_part = fractional_part - (int) fractional_part;
        fractional_size_in_string = fractional_size_in_string + 1;
    }
    char *dst = calloc(int_size_in_string + fractional_size_in_string + 2 + negative_shift, sizeof(char));
    if (dst == NULL) {
        perror("cannot allocate memory for dst array!");
        exit(1);
    }
    for (int k = 0; k < int_size_in_string + negative_shift; ++k) {
        dst[k] = integer_array[k];
    }
    dst[int_size_in_string + negative_shift] = '.';
    for (int j = 0; j < fractional_size_in_string; ++j) {
        dst[int_size_in_string + 1 + j + negative_shift] = (char) (fractional_array[j] + '0');
    }
    free(integer_array);
    free(fractional_array);
    return dst;
}

char *cha_to_str(char src) {
    char *dst = calloc(2, sizeof(char));
    if (dst == NULL) {
        perror("cannot allocate memory for dst array!");
        exit(1);
    }
    dst[0] = src;
    return dst;
}