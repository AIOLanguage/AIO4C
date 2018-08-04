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
void add_in_string_list(string_list *string_list, string source) {
    //Check to update capacity:
    update_memory_in_string_list(string_list);
    //Set string:
    string_list->strings[string_list->size] = source;
    string_list->size++;
}

boolean is_string_list_empty(string_list *string_list) {
    if (string_list->size == 0) {
        return 0;
    } else {
        return -1;
    }
}

void free_string_list(string_list *list){
    free(list);
}