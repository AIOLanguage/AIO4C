namespace lib4aio {

#ifndef LIB4AIO_STRING_UTILS_SPLIT_H
#define LIB4AIO_STRING_UTILS_SPLIT_H

    char **split_by_string(const char *src, const char *delimiter);

    char **split_by_space(const char *src);

    char **split_by_comma(const char *src);

    char **split_by_line_break(const char *src);

#endif //LIB4AIO_STRING_UTILS_SPLIT_H

}