#ifndef LIB4AIO_STRING_UTILS_COMMON_H
#define LIB4AIO_STRING_UTILS_COMMON_H


namespace lib4aio
{

    class struct_list;

    char *new_string(const char *src);

    char **filter_strings(
            const char **src,
            const unsigned src_size,
            bool (*filter_condition)(const char *)
    );

    char *join_to_string(const struct_list *src_strings, const char *delimiter);

    bool is_not_empty_string(const char *string);

    bool is_empty_string(const char *string);

    char *substring_by_offset(const char *string, const unsigned offset, const unsigned length);

    char *substring(const char *string, const unsigned start, const unsigned end);

    unsigned get_string_count(const char *const *src);

    bool are_equal_strings(const char *first, const char *second);

    void free_strings(char **src);

    void free_string(char *src);

}

#endif //LIB4AIO_STRING_UTILS_COMMON_H