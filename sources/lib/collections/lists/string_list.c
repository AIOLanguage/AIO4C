#include "../../../../headers/lib/collections/lists/string_list.h"
#include <string.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

//Passed JUnitTest!
string_list *new_string_list() {
    //Create string list:
    string_list *string_list = calloc(1, sizeof(string_list));
    if (string_list == NULL) {
        perror("cannot allocate memory for string_list");
        exit(1);
    }
    //Create capacity:
    string_list->capacity = 2;
    //Create size:
    string_list->size = 0;
    //Create char capacity that equals 2:
    string_list->strings = calloc(2, sizeof(char *));
    if (string_list->strings == NULL) {
        perror("can not allocate memory for strings in mutable_by_type list of string");
        exit(1);
    }
    return string_list;
}

//Passed JUnitTest!
void update_memory_in_string_list(string_list *string_list) {
    if (string_list->size + 1 == string_list->capacity) {
        string_list->capacity = string_list->capacity * 2;
        string_list->strings = realloc(string_list->strings, string_list->capacity * sizeof(char *));
    }
}

//Passed JUnitTests!
void add_in_string_list(string_list *string_list, char *string) {
    //Check to update capacity:
    update_memory_in_string_list(string_list);
    //Set string:
    string_list->strings[string_list->size] = calloc(1, sizeof(string));
    if (string_list->strings[string_list->size] == NULL) {
        perror("cannot allocate memory for string in list!");
        exit(1);
    }
    string_list->strings[string_list->size] = string;
    string_list->size++;
}

//Passed JUnitTests!
char *get_string_in_list_by_index(string_list *string_list, int index) {
    if (index < 0 || string_list->size <= index) {
        perror("cannot get index in string_list");
        exit(1);
    } else {
        return string_list->strings[index];
    }
}

int is_string_list_empty(string_list *string_list) {
    if (string_list->size == 0) {
        return 0;
    } else {
        return -1;
    }
}