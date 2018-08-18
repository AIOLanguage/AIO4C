#ifndef STRING_HOOK_UTILS_H
#define STRING_HOOK_UTILS_H

#include "../str_hook.h"
#include "../../point_watcher/point_watcher.h"

str_hook *new_str_hook_with_start(const_string source_ref, const int start_index);

str_hook *new_str_hook_with_end(const_string source_ref, const int end_index);

str_hook *new_str_hook_with_start_and_end(const_string source_ref, const int start_index, const int end_index);

str_hook *new_str_hook_by_point_watcher(const_string source_ref, const_point_watcher *watcher);

str_hook *new_str_hook_by_other_hook(const_str_hook *other_hook);

string substring_by_str_hook(const_str_hook *hook);

str_hook *new_str_hook_by_offset(const_string source_ref, const int offset, const int length);

int get_str_hook_size(const_str_hook *hook);

char get_str_hook_char(const_str_hook *hook, const int index);

const_boolean are_equal_hooked_str(const_str_hook *hook_1, const_str_hook *hook_2);

const_boolean is_str_hooked_word(const_str_hook *hook);

void reset_str_hook_positions(str_hook *hook);

#endif //STRING_HOOK_UTILS_H
