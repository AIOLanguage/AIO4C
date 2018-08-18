#ifndef STRING_PAIR_H
#define STRING_PAIR_H

#include "../string_utils/string_utils.h"

typedef struct string_pair {
    string first;
    string second;
} string_pair;

string_pair *new_string_pair(string first, string second);

#endif //STRING_PAIR_H