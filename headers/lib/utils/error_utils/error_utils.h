#ifndef ERROR_UTILS_H
#define ERROR_UTILS_H

void throw_error(const char *message);

void throw_error_with_tag(const char *tag, const char *message);

void throw_error_with_details(const char *tag, const char *message, const char *value);

#endif //ERROR_UTILS_H