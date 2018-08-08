#include "../boolean_utils/boolean_utils.h"

#ifndef CHAR_UTILS_H
#define CHAR_UTILS_H


boolean is_space(const char src);

boolean is_line_break(const char c);

boolean is_space_or_line_break(const char c);

boolean is_open_parenthesis(const char c);

boolean is_close_parenthesis(const char c);

boolean is_open_brace(const char c);

boolean is_close_brace(const char c);

boolean is_equal_sign(const char c);

boolean is_sign(const char c);

boolean is_dot(const char c);

#endif //CHAR_UTILS_H