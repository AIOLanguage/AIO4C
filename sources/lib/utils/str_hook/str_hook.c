#include "../../../../headers/lib/utils/str_hook/str_hook.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"

/**
 * String hook.
 */

str_hook *new_str_hook(const_string source_ref) {
    str_hook *hook = new_object(sizeof(str_hook));
    hook->source_ref = source_ref;
    hook->start = 0;
    hook->end = 0;
    return hook;
}

void free_str_hook(str_hook *hook) {
    free(hook);
}

void free_const_str_hook(const_str_hook *hook) {
    free((void *) hook);
}

/**
 * List.
 */

str_hook_list *new_str_hook_list() {
    str_hook_list *list = new_object(sizeof(str_hook_list));
    list->capacity = 2;
    list->size = 0;
    list->hooks = new_object_array(2, sizeof(str_hook));
    return list;
}

void update_memory_in_string_hook_list(str_hook_list *list) {
    if (list->size == list->capacity) {
        list->capacity = list->capacity * 2;
        list->hooks = realloc(list->hooks, list->capacity * sizeof(str_hook));
    }
}

void add_str_hook_in_list(str_hook_list *list, const_str_hook *hook) {
    update_memory_in_string_hook_list(list);
    list->hooks[list->size] = hook;
    list->size++;
}

void free_str_hooks_in_list(str_hook_list *list) {
    const_str_hook_array hooks = list->hooks;
    for (int i = 0; i < list->size; ++i) {
        const_str_hook *old_hook = hooks[i];
        if (old_hook != NULL) {
            hooks[i] = NULL;
            free((void *) old_hook);
        }
    }
}

void reset_str_hook_positions(str_hook *hook) {
    hook->start = 0;
    hook->end = 0;
}

void free_str_hook_list(str_hook_list *list) {
    free(list->hooks);
    free(list);
}