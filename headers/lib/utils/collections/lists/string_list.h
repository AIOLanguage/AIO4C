#ifndef STRING_LIST_H
#define STRING_LIST_H

typedef struct string_list {
    unsigned int capacity;
    unsigned int size;
    char **strings;
} string_list;

struct string_list *new_string_list();

void add_string_in_list(struct string_list *string_list, char *source);

void free_strings_in_list(struct string_list *list);

void free_string_list(struct string_list *list);

/**
 * Typedef utils.
 */

typedef const struct string_list const_string_list;

#endif //STRING_LIST_H