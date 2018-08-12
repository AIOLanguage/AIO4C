#ifndef ERROR_UTILS_H
#define ERROR_UTILS_H

#include "../string_utils/string_utils.h"

void throw_error(const_string message);

void throw_error_with_tag(const_string tag, const_string message);

void throw_error_string_with_details(const_string tag, const_string message, const_string value);

#endif //ERROR_UTILS_H