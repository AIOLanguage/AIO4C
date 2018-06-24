#ifndef STRING_LIST_H
#define STRING_LIST_H

//Passed JUnitTests!
typedef struct string_list {
    int capacity;
    int size;
    char **strings;
} string_list;

string_list *new_string_list();

void add_in_string_list(string_list *string_list, char *string);

char *get_string_in_list_by_index(string_list *listOfString, int index);

int is_string_list_empty(string_list *listOfString);

#endif //STRING_LIST_H