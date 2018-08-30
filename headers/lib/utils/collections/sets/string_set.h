#ifndef STRING_SET_H
#define STRING_SET_H

typedef struct string_set {
    unsigned int capacity;
    unsigned int size;
    char **strings;
} string_set;

struct string_set *new_string_set();

void add_string_in_set(struct string_set *set, char *string);

_Bool contains_string_in_set(struct string_set *set, const char *string);

void free_strings_in_set(struct string_set *set);

void free_string_set(struct string_set *set);

/**
 * Typedef utils.
 */

typedef const string_set const_string_set;

#endif //STRING_SET_H