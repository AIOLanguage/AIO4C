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
        perror("can not allocate memory for strings in mutable list of string");
        exit(1);
    }
}

//Passed JUnitTest!
void updateMemoryInListOfString(string_list *listOfString) {
    if (listOfString->size + 1 == listOfString->capacity) {
        listOfString->capacity = listOfString->capacity * 2;
        listOfString->strings = realloc(listOfString->strings, listOfString->capacity * sizeof(char *));
    }
}

//Passed JUnitTests!
void add_in_string_list(string_list *string_list, char *string) {
    //Check to update capacity:
    updateMemoryInListOfString(string_list);
    //Set string:
    string_list->strings[string_list->size] = calloc(1, sizeof(string));
    string_list->strings[string_list->size] = string;
    string_list->size = string_list->size + 1;
}

//Passed JUnitTests!
char *get_string_in_list_by_index(string_list *string_list1, int index) {
    if (index < 0 || string_list1->size <= index) {
        perror("cannot get index in string_list");
        exit(1);
    } else {
        return string_list1->strings[index];
    }
}

int is_string_list_empty(string_list *string_list1) {
    if (string_list1->size == 0) {
        return 0;
    } else {
        return -1;
    }
}