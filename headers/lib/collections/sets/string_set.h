#ifndef STRING_SET_H
#define STRING_SET_H

#include "../../utils/string_utils/string_utils.h"

typedef struct string_set {
    int capacity;
    int size;
    string_array strings;
} string_set;

string_set *new_string_set();

void add_string_in_set(string_set *set, string string);

boolean contains_string_in_set(string_set *set, const_string string);

void delete_string_set(string_set *set);

#endif //STRING_SET_H