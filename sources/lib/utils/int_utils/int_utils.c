#include <malloc.h>
#include <fcntl.h>
#include <ctype.h>
#include "../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../headers/lib/utils/int_utils/int_utils.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"

#define INT_UTILS_TAG "INT_UTILS"

#define INT_UTILS_DEBUG

#ifdef INT_UTILS_DEBUG

#endif

boolean matches_int(const_string string)
{
    const size_t length = strlen(string);
    int start = 0;
    if (length == 0) {
        return FALSE;
    }
    if (string[0] == '-') {
        if (length == 1) {
            return FALSE;
        }
        start = 1;
    }
    for (int i = start; i < length; ++i) {
        const char symbol = string[i];
        if (!isdigit(symbol)) {
            return FALSE;
        }
    }
    return TRUE;
}

int string_to_int(const_string string)
{
    const size_t length = strlen(string);
    int start = 0;
    const_boolean is_negative = is_minus_sign(string[0]);
    if (is_negative) {
        start++;
    }
    int result = 0;
    for (int i = start; i < length; i++) {
        const int digit = string[i] - '0';
        result = result * 10 + digit;
    }
    if (is_negative) {
        result *= -1;
    }
    return result;
}

/**
 * List.
 */

int_list *new_int_list()
{
    int_list *list = new_object(sizeof(struct int_list));
    list->capacity = 2;
    list->size = 0;
    list->values = new_object_array(2, sizeof(int));
    return list;
}

static void update_memory_in_int_list(int_list *list)
{
    if (list->size == list->capacity) {
        list->capacity = list->capacity * 2;
        list->values = reallocate_object_array(list->values, list->capacity, sizeof(int));
    }
}

void add_int_in_list(int_list *list, const int value)
{
    update_memory_in_int_list(list);
    list->values[list->size] = value;
    list->size++;
}

void free_int_list(int_list *list)
{
    free(list->values);
    free(list);
}