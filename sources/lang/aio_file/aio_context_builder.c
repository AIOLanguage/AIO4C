#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include <process.h>
#include <ctype.h>
#include <stdbool.h>
#include "../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lang/aio_types/aio_type.h"
#include "../../../headers/lib/collections/maps/aio_variable_map.h"

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
 * @param code_line - string that starts with return types;
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

/**
 * function is_valid_method_name:
 *
 * @param code_line - string that starts with method name;
 * @param method_name_ref - empty reference of string which will be filled with method name;
 * @param next_point - start point of rest code line. This is a next point for future parsing of code_line.
 * @return has string method name or not.
 */

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


/**
* function is_valid_args:
*
* @param code_line - string that starts with args;
* @param variable_map_ref - empty reference of variable map which will be filled with args;
* @param next_point - start point of rest code line. This is a next point for future parsing of code_line.
* @return valid args or not
*/

boolean is_valid_args(const_string code_line, aio_variable_map **variable_map_ref, int *next_point) {
    *variable_map_ref = new_aio_variable_map();
    const int code_line_length = strlen(code_line);
    for (int i = 0; i < code_line_length; ++i) {
        if (code_line[i] == ')') {
            const_string args_chunk = substring(code_line, 0, i);
            *next_point = i + 1;
            if (is_empty_string(args_chunk)) {
                return true;
            }
            string_array arg_chunks = split_by_comma(args_chunk);
            for (int j = 0; j < sizeof(arg_chunks); ++j) {
                string_array mu_type_vs_arg_chunks = split_by_spaces(arg_chunks[j]);
                string_array mu_vs_type_vs_arg = filter(mu_type_vs_arg_chunks, strings_size(
                        (const_string_array) mu_type_vs_arg_chunks), is_not_empty_string);
                boolean is_mutable = false;
                const_string type_string = NULL;
                const_string arg_name = NULL;
                switch (strings_size((const_string_array) mu_vs_type_vs_arg)) {
                    case 2:
                        is_mutable = false;
                        type_string = mu_vs_type_vs_arg[0];
                        arg_name = mu_vs_type_vs_arg[1];
                        break;
                    case 3:
                        if (strcmp(mu_vs_type_vs_arg[0], "mu") != 0) {
                            throw_error("invalid mutable modifier!");
                        } else {
                            is_mutable = true;
                        }
                        type_string = mu_vs_type_vs_arg[1];
                        arg_name = mu_vs_type_vs_arg[2];
                        break;
                    default:
                        throw_error("invalid method signature");
                }
                if (!contains_aio_type_in_set(type_string)) {
                    throw_error("cannot get aio type from method signature!");
                }
                aio_variable *arg = new_aio_arg(is_mutable, type_string, arg_name);
                put_aio_variable_in_map(*variable_map_ref, arg);
            }
            return true;
        }
    }
    return false;
}

void find_methods_in_manager(aio_context *context) {
    for (int i = 0; i < context->source_code->size; ++i) {
        string code_line = trim(context->source_code->strings[i]);
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
            aio_variable_map *arg_map;
            if (!is_valid_args(rest_args_and_brace, &arg_map, &next_point)) {
                throw_error("cannot get args!");
            }
            const_string rest_string = substring(code_line, next_point, code_line_length - next_point);
            const_string trim_rest_string = trim(rest_string);
            string_list *source_code = new_string_list();
            boolean is_found_open_brace = false;
            boolean is_found_close_brace = false;
            int start_body = 0;
            int up_down_counter = 0;
            int rest_length = strlen(trim_rest_string);
            for (int k = 0; k < strlen(trim_rest_string); ++k) {
                if (trim_rest_string[k] == '{') {
                    if (!is_found_open_brace) {
                        is_found_open_brace = true;
                        start_body = k + 1;
                    }
                    up_down_counter++;
                }
                if (trim_rest_string[k] == '}') {
                    if (is_found_open_brace) {
                        if (up_down_counter == 1) {
                            const_string source_code_string = substring(trim_rest_string, start_body, k - start_body);
                            add_in_string_list(source_code, source_code_string);
                            is_found_close_brace = true;
                            break;
                        } else {
                            up_down_counter--;
                        }
                    } else {
                        throw_error("body cannot starts with '}' !");
                    }
                }
            }
            if (!is_found_close_brace) {
                add_in_string_list(source_code, substring(trim_rest_string, start_body, rest_length - start_body));
                for (int j = i + 1; j < context->source_code->size; ++j) {
                    code_line = context->source_code->strings[j];
                    code_line_length = strlen(code_line);
                    for (int k = 0; k < code_line_length; ++k) {
                        if (trim_rest_string[k] == '{') {
                            if (!is_found_open_brace) {
                                is_found_open_brace = true;
                                start_body = k + 1;
                            }
                            up_down_counter++;
                        }
                        if (trim_rest_string[k] == '}') {
                            if (is_found_open_brace) {
                                if (up_down_counter == 1) {
                                    const_string source_code_string = substring(trim_rest_string, start_body,
                                                                                k - start_body);
                                    add_in_string_list(source_code, source_code_string);
                                    is_found_close_brace = true;
                                    break;
                                } else {
                                    up_down_counter--;
                                }
                            } else {
                                throw_error("body cannot starts with '}' !");
                            }
                        }
                    }
                }
            }
            if (!is_found_close_brace) {
                throw_error("cannot close method brace!");
            }
            aio_method_definition *method_definition = new_aio_method_definition(method_name, arg_map, source_code,
                                                                                 NULL);
        }
    }
}