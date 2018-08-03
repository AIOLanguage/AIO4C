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
    string_list *string_list = calloc(1, sizeof(string_list));
    //Create capacity:
    string_list->capacity = 2;
    //Create size:
    string_list->size = 0;
    //Create char capacity that equals 2:
    string_list->strings = calloc(2, sizeof(string));
    return string_list;
}

//Passed JUnitTest!
void update_memory_in_string_list(string_list *string_list) {
    if (string_list->size + 1 == string_list->capacity) {
        string_list->capacity = string_list->capacity * 2;
        string_list->strings = realloc(string_list->strings, string_list->capacity * sizeof(string));
    }
}

//Passed JUnitTests!
void add_in_string_list(string_list *string_list, char *source) {
    //Check to update capacity:
    printf("\nBEFORE UPDATE! %d-\n", string_list->size);
    printf("\nBEFORE UPDATE! %d-\n", string_list->capacity);
    update_memory_in_string_list(string_list);
    //Set string:
    printf("\nAFTER UPDATE! %d-\n", string_list->size);
    printf("\nAFTER UPDATE! %d-\n", string_list->capacity);
    string_list->strings[string_list->size] = source;
    printf("\nAFTER ASSIGN!-\n");
    string_list->size++;
}

boolean is_string_list_empty(string_list *string_list) {
    if (string_list->size == 0) {
        return 0;
    } else {
        return -1;
    }
}