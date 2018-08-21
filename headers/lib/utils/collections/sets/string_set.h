#ifndef STRING_SET_H
#define STRING_SET_H

#include "../../string_utils/string_utils.h"

typedef struct string_set {
    unsigned int capacity;
    unsigned int size;
    char **strings;
} string_set;

struct string_set *new_string_set();

void add_string_in_set(struct string_set *set, char *string);

_Bool contains_string_in_set(struct string_set *set, const char *string);

void delete_string_set(struct string_set *set);

#endif //STRING_SET_H