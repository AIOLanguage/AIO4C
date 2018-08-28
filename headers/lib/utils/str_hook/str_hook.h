#ifndef STRING_HOOK_H
#define STRING_HOOK_H

#include "../string_utils/string_utils.h"

/**
 * String hook.
 */

typedef struct str_hook {
    const_string source_string;
    int start;
    int end;
} str_hook;

/**
 * Define types.
 */

typedef const str_hook const_str_hook;

typedef str_hook **str_hook_array;

typedef const str_hook ** const_str_hook_array;

/**
 * Functions.
 */

str_hook *new_str_hook(const_string source_ref);

void free_str_hook(str_hook *hook);

void free_const_str_hook(const_str_hook *hook);

/**
 * List.
 */

typedef struct str_hook_list {
    size_t capacity;
    size_t size;
    const_str_hook_array hooks;
} str_hook_list;

typedef const str_hook_list const_str_hook_list;

/**
 * Functions.
 */

str_hook_list *new_str_hook_list();

void add_str_hook_in_list(str_hook_list *list, const_str_hook *hook);

void free_str_hooks_in_list(const_str_hook_list *list);

void free_str_hook_list(const_str_hook_list *list);

#endif //STRING_HOOK_H