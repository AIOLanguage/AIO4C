#ifndef STRING_HOOK_H
#define STRING_HOOK_H

/**
 * String hook.
 */

typedef struct str_hook {
    char *source_string;
    int start;
    int end;
} str_hook;

/**
 * Functions.
 */

struct str_hook *new_str_hook(char *source_ref);

void free_str_hook(struct str_hook *hook);

/**
 * List.
 */

typedef struct str_hook_list {
    unsigned capacity;
    unsigned size;
    struct str_hook **hooks;
} str_hook_list;

/**
 * Functions.
 */

struct str_hook_list *new_str_hook_list();

void add_str_hook_in_list(struct str_hook_list *list, struct str_hook *hook);

void free_str_hooks_in_list(struct str_hook_list *list);

void free_str_hook_list(struct str_hook_list *list);

/**
 * String hook iterator.
 */

typedef struct str_hook_iterator {
    struct str_hook_list *str_hook_list;
    unsigned current_hook_index;
    int position;
} str_hook_iterator;

/**
 * Functions.
 */

struct str_hook_iterator *new_str_hook_iterator();

struct str_hook_iterator *new_str_hook_iterator_by_list(
        struct str_hook_list *str_hook_list,
        const unsigned current_hook_index
);

_Bool next_in_str_hook_iterator(struct str_hook_iterator *iterator);

void free_str_hook_iterator(struct str_hook_iterator *iterator);

#endif //STRING_HOOK_H