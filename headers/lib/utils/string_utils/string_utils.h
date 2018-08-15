#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stddef.h>
#include "../boolean_utils/boolean_utils.h"

typedef _Bool boolean;

typedef const _Bool const_boolean;

typedef char *string;

typedef const char *const_string;

typedef char **string_array;

typedef const string_array const_string_array;

string new_string(const_string src);

string int_to_string(int src);

string double_to_string(double src);

string_array split_by_string(const_string src, const_string delimiter); //끝난!

string_array split_by_space(const_string src);

string_array split_by_comma(const_string src);

string trim_start(const_string src);

string trim_end(const_string src);

string trim(const_string src);

string squeeze_string(const_string src);

string_array trim_all(const_string_array strings, const int number_of_strings);

string trim_start_with_line_break(const_string src);

string trim_end_with_line_break(const_string src);

string trim_with_line_break(const_string src);

string_array trim_all_with_line_break(const_string_array strings, const int number_of_strings);

string remove_prefix(const_string src, const_string prefix); //끝난!

string remove_suffix(const_string src, const_string suffix); //끝난!

string remove_prefix_suffix(const_string src, const_string prefix, const_string suffix);

const_boolean starts_with_prefix(const_string src, const_string prefix);

const_boolean ends_with_suffix(const_string src, const_string suffix);

string_array filter(string_array src, int src_size, const_boolean (*filter_condition)(const_string));

const_boolean is_not_empty_string(const_string string);

const_boolean is_empty_string(const_string string);

string join_to_string(string_array src_strings, const_string delimiter, const int src_size);

const_boolean is_word(const_string line);

string substring_by_offset(const_string string, int offset, int length);

string substring(const_string string, int start, int end);

int strings_size(const_string_array src);

const_boolean matches_string(const_string word);

const_boolean are_equal_strings(const_string first, const_string second);

void free_strings(const_string_array *src_reference);

#endif //STRING_UTILS_H