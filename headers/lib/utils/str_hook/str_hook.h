#ifndef STRING_HOOK_H
#define STRING_HOOK_H

/**
 * String hook.
 */

typedef struct str_hook {
    const char *source_string;
    int start;
    int end;
} str_hook;

/**
 * Functions.
 */

struct str_hook *new_str_hook(const char *source_ref);

void free_str_hook(struct str_hook *hook);

void free_const_str_hook(const struct str_hook *hook);

/**
 * List.
 */

typedef struct str_hook_list {
    unsigned capacity;
    unsigned size;
    const struct str_hook **hooks;
} str_hook_list;

/**
 * Functions.
 */

struct str_hook_list *new_str_hook_list();

void add_str_hook_in_list(struct str_hook_list *list, const struct str_hook *hook);

void free_str_hooks_in_list(const struct str_hook_list *list);

void free_str_hook_list(const struct str_hook_list *list);

/**
 * Typedef utils.
 */

typedef const struct str_hook const_str_hook;

typedef struct str_hook **str_hook_array;

typedef const struct str_hook **const_str_hook_array;

typedef const str_hook_list const_str_hook_list;

#endif //STRING_HOOK_H