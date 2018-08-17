#include "../../../../headers/lib/collections/lists/string_list.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include <string.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

//Passed JUnitTest!
string_list *new_string_list() {
    //Create string list:
    string_list *list = calloc(1, sizeof(string_list));
    //Create capacity:
    list->capacity = 2;
    //Create size:
    list->size = 0;
    //Create char capacity that equals 2:
    list->strings = calloc(2, sizeof(string));
    return list;
}

//Passed JUnitTest!
void update_memory_in_string_list(string_list *string_list) {
    if (string_list->size == string_list->capacity) {
        string_list->capacity = string_list->capacity * 2;
        string_list->strings = realloc(string_list->strings, string_list->capacity * sizeof(string));
    }
}

//Passed JUnitTests!
void add_string_in_list(string_list *string_list, string source) {
    //Check from update capacity:
    update_memory_in_string_list(string_list);
    //Set string:
    string_list->strings[string_list->size] = source;
    string_list->size++;
}

void free_strings_in_list(string_list *list) {
    string_array strings = list->strings;
    for (int i = 0; i < list->size; ++i) {
        string old_string = strings[i];
        if (old_string != NULL) {
            strings[i] = NULL;
            free((void *) old_string);
        }
    }
}

void free_string_list(string_list *list) {
    free(list->strings);
    free(list);
}