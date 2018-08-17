#include "../../../../headers/lib/utils/string_hook/string_hook.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"

/**
 * String hook.
 */

string_hook *new_string_hook(const_string source_ref) {
    string_hook *hook = new_object(sizeof(string_hook));
    hook->source_ref = source_ref;
    hook->start = 0;
    hook->end = 0;
    return hook;
}

string_hook *new_string_hook_with_start(const_string source_ref, const int start_index) {
    string_hook *hook = new_object(sizeof(string_hook));
    hook->source_ref = source_ref;
    hook->start = start_index;
    hook->end = 0;
    return hook;
}

string_hook *new_string_hook_with_end(const_string source_ref, const int end_index) {
    string_hook *hook = new_object(sizeof(string_hook));
    hook->source_ref = source_ref;
    hook->start = 0;
    hook->end = end_index;
    return hook;
}

string_hook *new_string_hook_with_start_and_end(const_string source_ref, const int start_index, const int end_index) {
    string_hook *hook = new_object(sizeof(string_hook));
    hook->source_ref = source_ref;
    hook->start = start_index;
    hook->end = end_index;
    return hook;
}

string_hook *new_string_hook_by_point_watcher(const_string source_ref, const_point_watcher *watcher) {
    string_hook *hook = new_object(sizeof(string_hook));
    hook->source_ref = source_ref;
    hook->start = watcher->start;
    hook->end = watcher->end;
    return hook;
}

string_hook *new_string_hook_by_other_hook(const_string_hook *other_hook) {
    string_hook *hook = new_object(sizeof(string_hook));
    hook->source_ref = other_hook->source_ref;
    hook->start = other_hook->start;
    hook->end = other_hook->end;
    return hook;
}

string substring_by_string_hook(const_string_hook *hook) {
    return substring(hook->source_ref, hook->start, hook->end);
}

void free_string_hook(string_hook *hook) {
    free(hook);
}

/**
 * List.
 */

string_hook_list *new_string_hook_list() {
    string_hook_list *list = new_object(sizeof(string_hook_list));
    list->capacity = 2;
    list->size = 0;
    list->hooks = new_object_array(2, sizeof(string_hook));
    return list;
}

void update_memory_in_string_hook_list(string_hook_list *list) {
    if (list->size == list->capacity) {
        list->capacity = list->capacity * 2;
        list->hooks = realloc(list->hooks, list->capacity * sizeof(string_hook));
    }
}

void add_string_hook_in_list(string_hook_list *list, string_hook *hook) {
    update_memory_in_string_hook_list(list);
    list->hooks[list->size] = hook;
    list->size++;
}

void free_string_hooks_in_list(string_hook_list *list) {
    string_hook_array hooks = list->hooks;
    for (int i = 0; i < list->size; ++i) {
        string_hook *old_hook = hooks[i];
        if (old_hook != NULL) {
            hooks[i] = NULL;
            free((void *) old_hook);
        }
    }
}

void reset_string_hook_positions(string_hook *hook) {
    hook->start = 0;
    hook->end = 0;
}

void free_string_hook_list(string_hook_list *list) {
    free(list->hooks);
    free(list);
}