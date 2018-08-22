#ifndef STRING_HOOK_UTILS_H
#define STRING_HOOK_UTILS_H

#include "../str_hook.h"
#include "../../point_watcher/point_watcher.h"
#include "../../collections/sets/string_set.h"

str_hook *new_str_hook_with_start(const_string source_ref, const int start_index);

str_hook *new_str_hook_with_end(const_string source_ref, const int end_index);

str_hook *new_str_hook_with_start_and_end(const_string source_ref, const int start_index, const int end_index);

str_hook *new_str_hook_by_point_watcher(const_string source_ref, const_point_watcher *watcher);

str_hook *new_str_hook_by_other(const_str_hook *other_hook);

str_hook *new_str_hook_by_other_source_ref(const_str_hook *other_hook);

str_hook *new_str_hook_by_string(const_string source_ref);

string substring_by_str_hook(const_str_hook *hook);

str_hook *new_str_hook_by_offset(const_string source_ref, const int offset, const int length);

int get_str_hook_size(const_str_hook *hook);

char get_str_hook_char(const_str_hook *hook, const int index);

boolean are_equal_hooked_str(const_str_hook *hook_1, const_str_hook *hook_2);

boolean is_word_hooked(const_str_hook *hook);

void reset_str_hook_positions(str_hook *hook);

boolean is_hook_equals_str(const_str_hook *hook, const_string str);

boolean is_empty_hooked_str(const_str_hook *hook);

boolean is_not_empty_hooked_str(const_str_hook *hook);

boolean contains_string_in_set_by_hook(string_set *set, const_str_hook *hook);

str_hook_list *split_str_hook_by_string(const_str_hook *hook, const_string delimiter);

str_hook_list *split_str_hook_by_comma(const_str_hook *hook);

str_hook_list *split_str_hook_by_space(const_str_hook *hook);

str_hook_list *split_str_hook_by_line_break(const_str_hook *hook);

str_hook_list *split_str_hook_by_whitespace(const_str_hook *hook);

str_hook_list *split_str_hook_by_char_condition(const_str_hook *hook, boolean (*char_condition)(const char));

str_hook *trim_str_hook_by_start(const_str_hook *hook);

str_hook *trim_str_hook_by_end(const_str_hook *hook);

str_hook *trim_str_hook(const_str_hook *hook);

str_hook *trim_str_hook_with_line_break_by_start(const_str_hook *hook);

str_hook *trim_str_hook_with_line_break_by_end(const_str_hook *hook);

str_hook *trim_str_hook_with_line_break(const_str_hook *hook);

str_hook_list *trim_str_hook_list(const_str_hook_list *list);

str_hook_list *trim_str_hook_list_with_line_break(const_str_hook_list *list);

str_hook_list *filter_str_hook_list(const_str_hook_list *list, boolean (*filter_condition)(const_str_hook *));

void foreach_str_hook(const_str_hook_list *list, _inline void (*str_hook_action)(const_str_hook *hook));

void log_info_str_hook(const_string tag, const_string message, const struct str_hook *hook);

void log_info_str_hook_list(const_string tag, const_string message, const_str_hook_list *list);

void throw_error_with_hook(const_string tag, const_string message, const_str_hook *hook);

/**
 * Primitive type matchers.
 */

_Bool is_int_hooked(const struct str_hook *hook);

_Bool is_double_hooked(const struct str_hook *hook);

_Bool is_string_hooked(const struct str_hook *hook);

_Bool is_boolean_hooked(const struct str_hook *hook);

/**
 * Sign utils.
 */

_Bool is_more_or_equal_sign_hooked(const struct str_hook *hook, const int current_index);

_Bool is_less_or_equal_sign_hooked(const struct str_hook *hook, const int current_index);

_Bool is_double_equal_sign_hooked(const struct str_hook *hook, const int current_index);

/**
 * Casts.
 */

int str_hook_to_int(const struct str_hook *hook);

double str_hook_to_double(const struct str_hook *hook);

struct str_hook *lower_str_hook_quotes(const struct str_hook *hook);

_Bool str_hook_to_boolean(const struct str_hook* hook);

#endif //STRING_HOOK_UTILS_H