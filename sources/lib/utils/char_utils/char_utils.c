#include "../../../../headers/lib/utils/boolean_utils/boolean_utils.h"

boolean is_space(const char c) {
    return c == ' ';
}

boolean is_line_break(const char c) {
    return c == '\n';
}

boolean is_space_or_line_break(const char c) {
    return is_space(c) || is_line_break(c);
}

boolean is_open_parenthesis(const char c) {
    return c == '(';
}

boolean is_close_parenthesis(const char c) {
    return c == ')';
}

boolean is_open_brace(const char c) {
    return c == '{';
}

boolean is_close_brace(const char c) {
    return c == '}';
}

boolean is_equal_sign(const char c) {
    return c == '=';
}