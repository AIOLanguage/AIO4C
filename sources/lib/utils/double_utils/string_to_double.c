#include <mem.h>
#include <stdio.h>
#include <process.h>

int matches_double(const char *word) {
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

double string_to_double(const char *word) {
    if (matches_double(word) != 0) {
        perror("cannot convert string to double!");
        exit(1);
    }
    const int shift = 10;
    const char char_shift = '0';
    int integer_part = 0;
    int i = 0;
    while (1) {
        if (word[i] == '.') {
            break;
        } else {
            integer_part = integer_part * shift + (word[i++] - char_shift);
        }
    }
    double fraction_part = 0.0;
    int fraction_counter = 1;
    for (int j = i + 1; j < strlen(word); ++j) {
        fraction_part = fraction_part + (((double) (word[j] - char_shift)) / fraction_counter);
        fraction_counter = fraction_counter * shift;
    }
    return ((double) integer_part) + fraction_part;
}