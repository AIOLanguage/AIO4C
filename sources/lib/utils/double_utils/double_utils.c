#include <malloc.h>
#include <mem.h>
#include <ctype.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lib/utils/char_utils/char_utils.h"

#define DOUBLE_UTILS_DEBUG

#define DOUBLE_UTILS_TAG "DOUBLE_UTILS"

#ifdef DOUBLE_UTILS_DEBUG

#include "../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

boolean matches_double(const_string src)
{
    boolean was_dot = FALSE;
    boolean was_fraction = FALSE;
    int start = 0;
    const size_t length = strlen(src);
    if (length == 0) {
        return FALSE;
    }
    if (is_minus_sign(src[start])) {
        if (length == 1) {
            return FALSE;
        }
        start++;
    }
    if (!isdigit(src[start])) {
        return FALSE;
    } else {
        start++;
    }
    for (int i = start; i < length; ++i) {
        const char symbol = src[i];
        const_boolean is_digit = isdigit(symbol);
        if (!is_digit) {
            if (src[i] == '.' && !was_dot) {
                was_dot = TRUE;
            } else {
                return FALSE;
            }
        }
        if (is_digit && was_dot) {
            was_fraction = TRUE;
        }
    }
    return was_dot && was_fraction;
}

double string_to_double(const_string word)
{
    const static char CHAR_SHIFT = '0';
    const static int DIGIT_SHIFT = 10;
    const size_t length = strlen(word);
    int integer_part = 0;
    int i = 0;
    while (!is_dot(word[i])) {
        integer_part = integer_part * DIGIT_SHIFT + (word[i++] - CHAR_SHIFT);
    }
    double fraction_part = 0.0;
    double fraction_counter = DIGIT_SHIFT;
    for (int j = i + 1; j < length; ++j) {
        const double digit = ((double) (word[j] - CHAR_SHIFT) / fraction_counter);
        fraction_part += digit;
        fraction_counter *= DIGIT_SHIFT;
    }
    return ((double) integer_part) + fraction_part;
}