#include <string.h>
#include <malloc.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <lib4aio_cpp_headers/utils/memory_utils/memory_utils.h>
#include <lib4aio_cpp_headers/utils/struct_list/struct_list.h>

namespace lib4aio {
    static auto EMPTY_STRING = "";

    char *new_string(const char *src)
    {
        if (src) {
            char *new_string = (char *) new_object_array((unsigned) strlen(src) + 1, sizeof(char));
            strcpy(new_string, src);
            return new_string;
        } else {
            return nullptr;
        }
    }

    char **filter_strings(
            const char **src,
            const unsigned src_size,
            bool (*filter_condition)(const char *)
    )
    {
        auto are_valid_indices = static_cast<bool *>(new_object_array(src_size, sizeof(int)));
        unsigned new_length = 0;
        //Look at elements and measure new string:
        for (auto i = 0; i < src_size; ++i) {
            if (filter_condition(src[i])) {
                are_valid_indices[i] = true;
                new_length++;
            } else {
                are_valid_indices[i] = false;
            }
        }
        char **dst;
        if (new_length > 0) {
            dst = static_cast<char **>(new_object_array(new_length, sizeof(char *)));
        } else {
            dst = static_cast<char **>(new_object(sizeof(char *)));
            return dst;
        }
        auto new_pointer = 0;
        for (auto j = 0; j < src_size; ++j) {
            if (are_valid_indices[j]) {
                dst[new_pointer] = (char *) new_object_array((unsigned) strlen(src[j]) + 1, sizeof(char));
                strcpy(dst[new_pointer++], src[j]);
            }
        }
        return dst;
    }

    char *join_to_string(const struct_list *string_list, const char *delimiter)
    {
        const unsigned string_count = string_list->size;
        const unsigned delimiter_length = (const unsigned int) (strlen(delimiter));
        //Delimiters less than elements by 1:
        int current_string_length = -delimiter_length;
        for (unsigned i = 0; i < string_count; ++i) {
            //Get increased length of general string:
            current_string_length += strlen((char *) string_list->elements[i]) + delimiter_length;
        }
        if (current_string_length <= 0) {
            return (char *) (new_object_array(2, sizeof(char)));
        }
        char *dst = (char *) (new_object_array((const unsigned int) (current_string_length + 1), sizeof(char)));
        unsigned position = 0;
        for (unsigned j = 0; j < string_count; ++j) {
            const char *string = (char *) string_list->elements[j];
            const unsigned line_length = (const unsigned int) strlen(string);
            for (unsigned i = 0; i < line_length; ++i) {
                dst[position++] = string[i];
            }
            const bool is_last_chunk = j == string_count - 1;
            if (!is_last_chunk) {
                //Add delimiter
                for (unsigned i = 0; i < delimiter_length; ++i) {
                    dst[position++] = delimiter[i];
                }
            }
        }
        return dst;
    }

    bool is_not_empty_string(const char *string)
    {
        if (!string) {
            return false;
        }
        return !are_equal_strings(string, EMPTY_STRING);
    }

    bool is_empty_string(const char *string)
    {
        return are_equal_strings(string, EMPTY_STRING);
    }

    char *substring_by_offset(const char *string, const unsigned offset, const unsigned length)
    {
        auto dst = static_cast<char *>(new_object_array(length + 1, sizeof(char)));
        for (auto i = 0; i < length; ++i) {
            dst[i] = string[offset + i];
        }
        return dst;
    }

    char *substring(const char *string, const unsigned start, const unsigned end)
    {
        auto dst_size = end - start + 1;
        char *dst = static_cast<char *>(new_object_array(dst_size, sizeof(char)));
        auto position = 0;
        for (auto i = start; i < end; ++i) {
            dst[position++] = string[i];
        }
        return dst;
    }

    unsigned get_string_count(const char *const *src)
    {
        return static_cast<unsigned int>(malloc_usable_size((void *) src) / 4);
    }

    bool are_equal_strings(const char *first, const char *second)
    {
        return strcmp(first, second) == 0;
    }

    void free_strings(char **src)
    {
        auto length = get_string_count(src);
        for (auto i = 0; i < length; ++i) {
            free(src[i]);
        }
        free(src);
    }

    void free_string(char *src)
    {
        if (src) {
            free(src);
        }
    }
}