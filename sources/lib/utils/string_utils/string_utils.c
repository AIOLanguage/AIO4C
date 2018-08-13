#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <assert.h>
#include <stddef.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../headers/lib/utils/log_utils/log_utils.h"

#define STRING_UTILS_TAG "STRING_UTILS"

string new_string(const_string src) {
    string new_string = calloc(strlen(src) + 1, sizeof(char));
    strcpy(new_string, src);
    return new_string;
}

//박수!
//Passed JUnitTest!
string_array filter(string_array src, int src_size, const_boolean (*filter_condition)(const_string)) {
    int *new_indices = calloc((size_t) src_size, sizeof(int));
    char **dst;
    size_t new_length = 0;
    //Look at values and measure new string:
    for (int i = 0; i < src_size; ++i) {
        if (filter_condition(src[i]) == 0) {
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
    if (string == NULL) {
        return FALSE;
    }
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
string join_to_string(string_array src_strings, const_string delimiter, const int src_size) {
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
string substring_by_offset(const_string string, int offset, int length) {
    char *dst = calloc((size_t) (length + 1), sizeof(char));
    for (int i = 0; i < length; ++i) {
        dst[i] = string[offset + i];
    }
    return dst;
}

string substring(const_string string, int start, int end) {
    const size_t dst_size = (const size_t) (end - start + 1);
    char* dst = calloc(dst_size, sizeof(char));
    int position = 0;
    for (int i = start; i < end; ++i) {
        dst[position++] = string[i];
    }
    return dst;
}

int strings_size(const_string_array src) {
    return _msize(src) / 4;
}

void free_strings(const_string_array *src_reference) {
    for (int i = 0; i < strings_size(*src_reference); ++i) {
        free((void *) (*src_reference)[i]);
    }
    free(*src_reference);
}

string squeeze_string(const_string src) {
    const unsigned src_length = strlen(src);
    string dst = calloc(src_length + 1, sizeof(char));
    int position = 0;
    for (int i = 0; i < src_length; ++i) {
        const char symbol = src[i];
        if (!is_space_or_line_break(symbol)) {
            dst[position++] = symbol;
        }
    }
    dst = realloc(dst, position * sizeof(char));
    return dst;
}

//Passed JUnitTest!
const_boolean matches_string(const_string word) {
    boolean result = FALSE;
    int length = strlen(word);
    if (length > 1 && word[0] == '\'' && word[length - 1] == '\'') {
        result = TRUE;
    }
    return result;
}

//Passed JUnitTest!
string int_to_string(int src) {
    int division = src;
    unsigned int_size_in_string = 0;
    while (division != 0) {
        division = division / 10;
        int_size_in_string = int_size_in_string + 1;
    }
    string integer_array;
    int negative_shift = 0;
    if (int_size_in_string > 0) {
        if (src < 0) {
            negative_shift = 1;
        }
        integer_array = calloc(int_size_in_string + 1 + negative_shift, sizeof(char));
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

string double_to_string(double src) {
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