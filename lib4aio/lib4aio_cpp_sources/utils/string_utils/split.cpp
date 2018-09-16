#include <string.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <lib4aio_cpp_headers/utils/memory_utils/memory_utils.h>
#include <lib4aio_cpp_headers/utils/string_utils/split.h>

namespace lib4aio
{
    static auto COMMA = ",";

    static auto SPACE = " ";

    static auto LINE_BREAK = "\n";

    static void move_string_to_dst(const char *src, const unsigned string_length, char ***dst)
    {
        //Allocate memory for string array:
        *dst = static_cast<char **>(new_object(sizeof(string)));
        //Allocate memory for only string:
        **dst = static_cast<string>(new_object_array(string_length, sizeof(char) + 1));
        strcpy(**dst, src);
    }

    static void move_empty_string_to_dst(const char *src, char ***dst)
    {
        move_string_to_dst(src, 1, dst);
    }

    static void create_left_part(const char *src, const unsigned *indices, size_t delimiter_length, char ***dst)
    {
        (*dst)[0] = static_cast<string>(new_object_array(
                indices[0] - delimiter_length + 2,
                sizeof(char))
        );
        for (auto i = 0; i < indices[0] - delimiter_length; ++i) {
            (*dst)[0][i] = src[i];
        }
    }

    static void create_right_part(const char *src, const unsigned *indices, char ***dst, int pointers, size_t length)
    {
        (*dst)[pointers] = static_cast<string>(
                new_object_array(length - indices[pointers - 1] + 1,
                                 sizeof(char))
        );
        auto k = 0;
        for (auto i = indices[pointers - 1]; i < length; ++i) {
            (*dst)[pointers][k] = src[i];
            k = k + 1;
        }
    }

    char **split_by_comma(const_string src)
    {
        auto result = split_by_string(src, COMMA);
        return result;
    }

    char **split_by_space(const_string src)
    {
        auto result = split_by_string(src, SPACE);
        return result;
    }

    char **split_by_line_break(const_string src)
    {
        auto result = split_by_string(src, LINE_BREAK);
        return result;
    }

    char **split_by_string(const_string src, const_string delimiter)
    {
        char **dst;
        auto src_length = strlen(src);
        //Is empty string:
        if (src_length < 1 || are_equal_strings(delimiter, "")) {
            move_empty_string_to_dst(src, &dst);
            return dst;
        }
        //Create split indices:
        auto indices = static_cast<unsigned int *>(new_object_array(src_length, sizeof(int)));
        auto delimiter_length = strlen(delimiter);
        unsigned pointers = 0;
        //Mark split points:
        for (unsigned i = 0; i < src_length; ++i) {
            auto result = 0;
            while (result == 0) {
                for (auto j = 0; j < delimiter_length; ++j) {
                    if (src[i + j] != delimiter[j]) {
                        result = -1;
                        break;
                    }
                }
                if (result == 0) {
                    i += delimiter_length;
                    indices[pointers] = i;
                    pointers++;
                }
            }
        }
        //Cannot find points:
        if (pointers == 0) {
            move_string_to_dst(src, src_length, &dst);
            return dst;
        }
        indices = static_cast<unsigned int *>(reallocate_object_array(
                indices,
                pointers,
                sizeof(unsigned)
        ));
        //Parts more than pointers by 1:
        auto parts = pointers + 1;
        dst = static_cast<char **>(new_object_array(parts, sizeof(char *)));
        //Create left part:
        create_left_part(src, indices, delimiter_length, &dst);
        //Create right part:
        create_right_part(src, indices, &dst, pointers, src_length);
        //Create middle parts:
        if (pointers > 1) {
            //From second delimiter:
            for (auto j = 0; j < pointers - 1; ++j) {
                if (indices[j + 1] - indices[j] - delimiter_length > 0) {
                    dst[j + 1] = static_cast<char *>(new_object_array(
                            indices[j + 1] - indices[j] - delimiter_length + 1,
                            sizeof(char))
                    );
                    for (auto i = 0; i < indices[j + 1] - indices[j] - delimiter_length; ++i) {
                        dst[j + 1][i] = src[indices[j] + i];
                    }
                } else {
                    dst[j + 1] = static_cast<char *>(new_object_array(2, sizeof(char)));
                    dst[j + 1] = const_cast<char *>("");
                }
            }
        }
        return dst;
    }
};