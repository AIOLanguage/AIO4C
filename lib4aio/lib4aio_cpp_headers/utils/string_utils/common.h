namespace lib4aio
{

#ifndef LIB4AIO_STRING_UTILS_COMMON_H
#define LIB4AIO_STRING_UTILS_COMMON_H

    char *new_string(const char *src);

    char **filter_strings(
            const char **src,
            const unsigned src_size,
            bool (*filter_condition)(const char *)
    );

    char *join_to_string(
            const char **src_strings,
            const char *delimiter,
            const unsigned src_size
    );

    bool is_not_empty_string(const char *string);

    bool is_empty_string(const char *string);

    char *substring_by_offset(const char *string, int offset, int length);

    char *substring(const char *string, int start, int end);

    int get_string_array_size(const char **src);

    bool are_equal_strings(const char *first, const char *second);

    void free_strings(char **src);

    void free_string(char *src);

/**
 * Typedef utils.
 */

    typedef char *string;

    typedef const char *const_string;

#endif //LIB4AIO_STRING_UTILS_COMMON_H
}