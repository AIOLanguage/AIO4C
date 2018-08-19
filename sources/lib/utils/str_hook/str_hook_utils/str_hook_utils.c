#include <ctype.h>
#include <mem.h>
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/lib/utils/point_watcher/point_watcher.h"
#include "../../../../../headers/lib/utils/collections/sets/string_set.h"
#include "../../../../../headers/lib/utils/str_hook/str_hook.h"

str_hook *new_str_hook_with_start(const_string source_ref, const int start_index) {
    str_hook *hook = new_object(sizeof(str_hook));
    hook->source_ref = source_ref;
    hook->start = start_index;
    hook->end = 0;
    return hook;
}

str_hook *new_str_hook_with_end(const_string source_ref, const int end_index) {
    str_hook *hook = new_object(sizeof(str_hook));
    hook->source_ref = source_ref;
    hook->start = 0;
    hook->end = end_index;
    return hook;
}

str_hook *new_str_hook_with_start_and_end(const_string source_ref, const int start_index, const int end_index) {
    str_hook *hook = new_object(sizeof(str_hook));
    hook->source_ref = source_ref;
    hook->start = start_index;
    hook->end = end_index;
    return hook;
}

str_hook *new_str_hook_by_point_watcher(const_string source_ref, const_point_watcher *watcher) {
    str_hook *hook = new_object(sizeof(str_hook));
    hook->source_ref = source_ref;
    hook->start = watcher->start;
    hook->end = watcher->end;
    return hook;
}

str_hook *new_str_hook_by_other(const_str_hook *other_hook) {
    str_hook *hook = new_object(sizeof(str_hook));
    hook->source_ref = other_hook->source_ref;
    hook->start = other_hook->start;
    hook->end = other_hook->end;
    return hook;
}

str_hook *new_str_hook_by_other_source_ref(const_str_hook *other_hook) {
    str_hook *hook = new_object(sizeof(str_hook));
    hook->source_ref = other_hook->source_ref;
    hook->start = 0;
    hook->end = 0;
    return hook;
}

str_hook *new_str_hook_by_string(const_string source_ref) {
    str_hook *hook = new_object(sizeof(str_hook));
    hook->source_ref = source_ref;
    hook->start = 0;
    hook->end = strlen(source_ref);
    return hook;
}

str_hook *new_str_hook_by_offset(const_string source_ref, const int offset, const int length) {
    str_hook *hook = new_object(sizeof(str_hook));
    hook->source_ref = source_ref;
    hook->start = offset;
    hook->end = offset + length;
    return hook;
}

int get_str_hook_size(const_str_hook *hook) {
    return hook->end - hook->start;
}

char get_str_hook_char(const_str_hook *hook, const int index) {
    return hook->source_ref[0];
}

boolean is_word_hooked(const_str_hook *hook) {
    int length = get_str_hook_size(hook);
    if (length < 1) {
        return FALSE;
    }
    const char first_symbol = get_str_hook_char(hook, 0);
    if (isalpha(first_symbol)) {
        if (length > 1) {
            for (int i = 1; i < length; ++i) {
                const char symbol = get_str_hook_char(hook, i);
                if (!isalnum(symbol)) {
                    return FALSE;
                }
            }
        }
    }
    return TRUE;
}

string substring_by_str_hook(const_str_hook *hook) {
    return substring(hook->source_ref, hook->start, hook->end);
}

boolean are_equal_hooked_str(const_str_hook *hook_1, const_str_hook *hook_2) {
    const int size_1 = get_str_hook_size(hook_1);
    const int size_2 = get_str_hook_size(hook_2);
    if (size_1 != size_2) {
        return FALSE;
    }
    const_string str_1 = hook_1->source_ref;
    const_string str_2 = hook_2->source_ref;
    const int start_1 = hook_1->start;
    const int start_2 = hook_2->start;
    for (int i = 0; i < size_1; ++i) {
        if (str_1[start_1 + i] != str_2[start_2 + i]) {
            return FALSE;
        }
    }
    return TRUE;
}

boolean is_hooked_str_equals_str(const_str_hook *hook, const_string str) {
    const int hook_size = get_str_hook_size(hook);
    const int str_length = strlen(str);
    if (hook_size != str_length) {
        return FALSE;
    }
    const_string hooked_str = hook->source_ref;
    const int start = hook->start;
    for (int i = 0; i < hook_size; ++i) {
        if (hooked_str[start + i] != str[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

boolean contains_string_in_set_by_hook(string_set *set, const_str_hook *hook) {
    for (int i = 0; i < set->size; ++i) {
        if (is_hooked_str_equals_str(hook, set->strings[i])) {
            return TRUE;
        }
    }
    return FALSE;
};

boolean is_empty_hooked_str(const_str_hook *hook) {
    return hook->end - hook->start <= 0;
}

str_hook_list *filter_str_hook_list(const_str_hook_list *list, boolean (*filter_condition)(const_str_hook *)) {
    const size_t src_list_size = list->size;
    const_str_hook_array src_hooks = list->hooks;
    str_hook_list *new_hook_list = new_str_hook_list();
    for (int k = 0; k < src_list_size; ++k) {
        const_str_hook *src_hook = src_hooks[k];
        if (filter_condition(src_hook)) {
            const_str_hook *new_hook = new_str_hook_by_other(src_hook);
            add_str_hook_in_list(new_hook_list, new_hook);
        }
    }
    return new_hook_list;
}