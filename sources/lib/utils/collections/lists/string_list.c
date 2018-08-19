#include <string.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/lib/utils/collections/lists/string_list.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"

string_list *new_string_list() {
    string_list *list = new_object(sizeof(string_list));
    list->capacity = 2;
    list->size = 0;
    list->strings = new_object_array(2, sizeof(string));
    return list;
}

static void update_memory_in_string_list(string_list *string_list) {
    if (string_list->size == string_list->capacity) {
        string_list->capacity = string_list->capacity * 2;
        string_list->strings = realloc(string_list->strings, string_list->capacity * sizeof(string));
    }
}

void add_string_in_list(string_list *string_list, string source) {
    update_memory_in_string_list(string_list);
    string_list->strings[string_list->size] = source;
    string_list->size++;
}

void free_strings_in_list(string_list *list) {
    const_string_array strings = list->strings;
    for (int i = 0; i < list->size; ++i) {
        const_string old_string = strings[i];
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