#ifndef CHAR_UTILS_H
#define CHAR_UTILS_H

_Bool is_space(const char src);

_Bool is_line_break(const char c);

_Bool is_space_or_line_break(const char c);

_Bool is_opening_parenthesis(const char c);

_Bool is_closing_parenthesis(const char c);

_Bool is_opening_brace(const char c);

_Bool is_closing_brace(const char c);

_Bool is_equal_sign(const char c);

_Bool is_sign(const char c);

_Bool is_dot(const char c);

_Bool is_colon(const char c);

_Bool is_comma(const char c);

_Bool is_single_quote(const char c);

#endif //CHAR_UTILS_H