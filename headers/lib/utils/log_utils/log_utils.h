#ifndef LOG_UTILS_H
#define LOG_UTILS_H

void log_info(const_string tag, const_string message);

void log_info_string(const_string tag, const_string message, const_string value);

void log_info_char(const_string tag, const_string message, const char value);

void log_info_double(const_string tag, const double value);

void log_info_int(const_string tag, const_string message, const int value);

void log_info_boolean(const_string tag, const_string message, const_boolean value);

#endif //LOG_UTILS_H