#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include <process.h>
#include <ctype.h>
#include <stdbool.h>
#include "../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../headers/lang/aio_file/aio_file.h"
#include "../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lang/aio_types/aio_type.h"
#include "../../../headers/lib/collections/maps/aio_variable_map.h"

boolean is_valid_args(const_string code_line, aio_variable_map *variable_map_ref, int *next_point);

const_string extract_name_from_path(const_string path) {
    if (ends_with_suffix(path, AIO_SUFFIX)) {
        const int last_index = strlen(path) - 1;
        for (int i = last_index; i >= 0; --i) {
            const char symbol = path[i];
            if (symbol == '/') {
                string aio_file_name = substring(path, i + 1, last_index - i - AIO_SUFFIX_LENGTH);
                if (is_word(aio_file_name)) {
                    return aio_file_name;
                } else {
                    throw_error("invalid aio_file_name:0!");
                }
            } else {
                throw_error("invalid aio_file_name:1!");
            }
        }
    } else {
        throw_error("invalid aio_file_name:2!");
    }
}

/**
 * function is_valid_return_types:
 *
 * @param code_line - string, method signature;
 * @param ref_list - empty reference of string list which will be filled with return types;
 * @param next_point - start point of rest code line. This is a next point for future parsing of code_line.
 * @return has string method return types or not.
 */

boolean is_valid_return_types(const_string code_line, string_list **ref_list, int *next_point) {
    *ref_list = new_string_list();
    boolean is_return_cortege = code_line[0] == '(';
    const unsigned code_line_length = strlen(code_line);
    if (is_return_cortege) {
        for (int i = 1; i < code_line_length; ++i) {
            if (code_line[i] == ')') {
                const_string return_types_smooth_chunk = substring(code_line, 1, i - 2); //minus two parenthesises
                const_string squeeze_return_types_smooth_chunk = squeeze_string(return_types_smooth_chunk);
                string_array return_type_chunks = split_by_comma(squeeze_return_types_smooth_chunk);
                const int return_type_chunks_size = strings_size((const_string_array) return_type_chunks);
                if (return_type_chunks_size == 0) {
                    throw_error("aio return type must be declared explicitly!");
                }
                for (int j = 0; j < return_type_chunks_size; ++j) {
                    if (contains_aio_type_in_set(return_type_chunks[i])) {
                        add_in_string_list(*ref_list, return_type_chunks[i]);
                    } else {
                        throw_error("cannot identify aio type!");
                    }
                }
                *next_point = i + 1;
                return true;
            }
        }
    } else { //is simple return type
        for (int i = 0; i < code_line_length; ++i) {
            if (code_line[i] == ' ') {
                const_string return_type_chunk = substring(code_line, 0, i);
                if (contains_aio_type_in_set(return_type_chunk)) {
                    if (strcmp(return_type_chunk, VOID) != 0) {
                        add_in_string_list(*ref_list, return_type_chunk);
                    }
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
}

boolean is_valid_method_name(const_string code_line, const_string *method_name_ref, int *next_point) {
    const int code_line_length = strlen(code_line);
    for (int i = 0; i < code_line_length; ++i) {
        if (code_line[i] == '(') {
            const_string method_name_chunk = substring(code_line, 0, i);
            const_string method_name = trim_end(method_name_chunk);
            if (!is_word(method_name)) {
                throw_error("invalid method name!");
            }
            *method_name_ref = method_name;
            *next_point = i + 1;
            return true;
        }
    }
    return false;
}

void find_methods_in_manager(aio_file *aio_object) {
    for (int i = 0; i < aio_object->source_code->size; ++i) {
        const_string code_line = trim(aio_object->source_code->strings[i]);
        int code_line_length = strlen(code_line);
        if (code_line_length > 1) {
            if (starts_with_prefix(code_line, AIO_COMMENTS)) {
                continue;
            }
            //try to read return method type & put in return_type_string (example: Int, Dou, Str):
            string_list *return_type_string;
            int next_point;
            if (!is_valid_return_types(code_line, &return_type_string, &next_point)) {
                throw_error("cannot get return type!");
            }
            const_string without_return_type_string = substring(code_line, next_point, code_line_length - next_point);
            const_string trim_without_return_type_string = trim_start(without_return_type_string);
            const_string method_name;
            if (!is_valid_method_name(trim_without_return_type_string, &method_name, &next_point)) {
                throw_error("cannot get method name!");
            }
            const_string rest_args_and_brace = substring(code_line, next_point, code_line_length - next_point);
            aio_variable_map arg_map;
            if (!is_valid_args(rest_args_and_brace, &arg_map, &next_point)) {
                throw_error("cannot get args!");
            }
            const_string rest_string = substring(code_line, next_point, code_line_length - next_point);
            const_string trim_rest_string = trim(rest_string);
            if (strcmp(trim_rest_string, "{") != 0) {
                throw_error("cannot get open brace");
            }
        }
    }
}

boolean is_valid_args(const_string code_line, aio_variable_map *variable_map_ref, int *next_point) {







    const int code_line_length = strlen(code_line);


    for (int i = 0; i < code_line_length; ++i) {
        if ()



    }


    return 0;
}