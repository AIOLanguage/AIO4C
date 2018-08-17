#ifndef STRING_HOOK_H
#define STRING_HOOK_H

#include "../string_utils/string_utils.h"
#include "../../point_watcher/point_watcher.h"

/**
 * String hook.
 */

typedef struct string_hook {
    const_string source_ref;
    int start;
    int end;
} string_hook;

/**
 * Define types.
 */

typedef const string_hook const_string_hook;

typedef string_hook **string_hook_array;

typedef const string_hook_array const_string_hook_array;

/**
 * Functions.
 */

string_hook *new_string_hook(const_string source_ref);

string_hook *new_string_hook_with_start(const_string source_ref, const int start_index);

string_hook *new_string_hook_with_end(const_string source_ref, const int end_index);

string_hook *new_string_hook_with_start_and_end(const_string source_ref, const int start_index, const int end_index);

string_hook *new_string_hook_by_point_watcher(const_string source_ref, const_point_watcher *watcher);

string_hook *new_string_hook_by_other_hook(const_string_hook *other_hook);

string substring_by_string_hook(const_string_hook *hook);

void reset_string_hook_positions(string_hook *hook);

void free_string_hook(string_hook *hook);

/**
 * List.
 */

typedef struct string_hook_list {
    int capacity;
    int size;
    string_hook_array hooks;
} string_hook_list;

/**
 * Functions.
 */

string_hook_list *new_string_hook_list();

void add_string_hook_in_list(string_hook_list *list, string_hook *hook);

void free_string_hooks_in_list(string_hook_list *list);

void free_string_hook_list(string_hook_list *list);

#endif //STRING_HOOK_H