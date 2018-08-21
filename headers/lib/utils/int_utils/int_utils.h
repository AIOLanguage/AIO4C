#ifndef INT_UTILS_H
#define INT_UTILS_H

_Bool matches_int(const char *string);

int string_to_int(const char *string);

/**
 * List.
 */

typedef struct int_list {
    unsigned int capacity;
    unsigned int size;
    int *values;
} int_list;

struct int_list *new_int_list();

void add_int_in_list(struct int_list *list, const int value);

void free_int_list(struct int_list *list);

/**
 * Typedef utils.
 */

typedef int *int_array;

typedef const int *const_int_array;

#endif //INT_UTILS_H