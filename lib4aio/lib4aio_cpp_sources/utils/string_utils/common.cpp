#include <string.h>
#include <malloc.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <lib4aio_cpp_headers/utils/memory_utils/memory_utils.h>

namespace lib4aio
{
    static auto EMPTY_STRING = "";

    char *new_string(const char *src)
    {
        if (src) {
            string new_string = static_cast<string>(new_object_array(strlen(src) + 1, sizeof(char)));
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
                dst[new_pointer] = static_cast<string>(new_object_array(
                        strlen(src[j]) + 1,
                        sizeof(char))
                );
                strcpy(dst[new_pointer++], src[j]);
            }
        }
        return dst;
    }

    char *join_to_string(
            const char **src_strings,
            const char *delimiter,
            const unsigned src_size
    )
    {
        char *dst;
        auto delimiter_length = strlen(delimiter);
        //Delimiters less than elements by 1:
        auto current_string_length = 0 - delimiter_length;
        for (auto i = 0; i < src_size; ++i) {
            //Get increase length of general string:
            current_string_length += strlen(src_strings[i]) + delimiter_length;
        }
        if (current_string_length == 0) {
            dst = static_cast<string>(new_object_array(2, sizeof(char)));
            return dst;
        }
        dst = static_cast<string >(new_object_array(
                current_string_length + 1,
                sizeof(char))
        );
        auto position = 0;
        for (auto j = 0; j < src_size; ++j) {
            auto line_length = strlen(src_strings[j]);
            for (auto i = 0; i < line_length; ++i) {
                dst[position] = src_strings[j][i];
                position = position + 1;
            }
            if (j != src_size - 1) {
                for (auto i = 0; i < delimiter_length; ++i) {
                    dst[position] = delimiter[i];
                    position = position + 1;
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

    unsigned get_string_array_size(const char *const *src)
    {
        return static_cast<unsigned int>(malloc_usable_size((void *) src) / 4);
    }

    bool are_equal_strings(const char *first, const char *second)
    {
        return strcmp(first, second) == 0;
    }

    void free_strings(char **src)
    {
        auto length = get_string_array_size(src);
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