#include <ctype.h>
#include "../../../../../headers/lib/utils/string_hook/str_hook.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/lib/utils/point_watcher/point_watcher.h"

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

str_hook *new_str_hook_by_other_hook(const_str_hook *other_hook) {
    str_hook *hook = new_object(sizeof(str_hook));
    hook->source_ref = other_hook->source_ref;
    hook->start = other_hook->start;
    hook->end = other_hook->end;
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

const_boolean is_str_hooked_word(const_str_hook *hook) {
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

const_boolean are_equal_hooked_str(const_str_hook *hook_1, const_str_hook *hook_2) {
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