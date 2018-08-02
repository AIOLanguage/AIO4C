#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stddef.h>
#include "../boolean_utils/boolean_utils.h"

#define TRUE 0
#define FALSE (-1)

typedef char *string;

typedef const char *const_string;

typedef char **string_array;

typedef const char **const_string_array;

string int_to_string(int src);

string double_to_string(double src);

string_array split_by_string(const_string src, const_string delimiter); //끝난!

string_array split_by_spaces(const_string src);

string_array split_by_comma(const_string src);

string trim_start(const_string src);

string trim_end(const_string src);

string trim(const_string src);

string squeeze_string(const_string src);

boolean is_white_space(char src);

string_array trim_all(const_string_array strings, int number_of_strings);

string remove_prefix(const_string src, const_string prefix); //끝난!

string remove_suffix(const_string src, const_string suffix); //끝난!

string remove_prefix_suffix(const_string src, const_string prefix, const_string suffix);

boolean starts_with_prefix(const_string src, const_string prefix);

boolean ends_with_suffix(const_string src, const_string suffix);

string_array filter(string_array src, int src_size, const_boolean (*filter_function)(const_string));

const_boolean is_not_empty_string(const_string string);

boolean is_empty_string(const_string string);

const_string join_to_string(const_string_array src_strings, const_string delimiter, int src_size);

boolean is_word(const_string line);

string substring(const_string string, int offset, int length);

void concat_string_to_string(string dst, const_string src);

void concat_char_to_string(string *dst, char src);

int strings_size(const_string_array src);

boolean matches_string(const_string word);

void delete_strings(const_string_array src);

#endif //STRING_UTILS_H