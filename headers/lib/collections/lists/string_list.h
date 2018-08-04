#ifndef STRING_LIST_H
#define STRING_LIST_H

#include "../../utils/boolean_utils/boolean_utils.h"
#include "../../utils/string_utils/string_utils.h"

//Passed JUnitTests!
typedef struct string_list {
    int capacity;
    int size;
    string_array strings;
} string_list;

string_list *new_string_list();

void add_string_in_list(string_list *string_list, string source);

boolean is_string_list_empty(string_list *string_list);

void free_string_list(string_list *list);

#endif //STRING_LIST_H