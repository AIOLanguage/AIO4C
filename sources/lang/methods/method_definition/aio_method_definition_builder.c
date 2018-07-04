#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include <ctype.h>
#include <process.h>
#include "../../../../headers/lang/object/object_manager/aio_nexus.h"
#include "../../../../headers/lib/collections/lists/string_list.h"
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lib/utils/operation_utils/operation_utils.h"

aio_nexus *core;

//Passed JUnitTest!
string_list *get_source_code_of_method(char *method_name, string_list *source_code, int start_index) {
    string_list *method_code = new_string_list();
    int current_index = start_index;
    char *trimmed_line = trim(source_code->strings[current_index]);
    if (strcmp(trimmed_line, "") != 0) {
        char *clean_first_line = remove_prefix(trimmed_line, method_name);
        if (strcmp(clean_first_line, "") != 0) {
            add_in_string_list(method_code, clean_first_line);
        }
        while (++current_index < source_code->size) {
            char *current_line = trim(source_code->strings[current_index]);
            if (strcmp(current_line, "") == 0) {
                break;
            } else {
                add_in_string_list(method_code, current_line);
            }
        }
    }
    return method_code;
}

//While empty method:
aio_annotation_list *get_annotations_of_method(char *method_name, string_list *source_code, int start_index) {
    aio_annotation_list *annotations = new_annotation_list();
    //Not ready:
    return annotations;
}

//Passed JUnitTest!
int is_correct_placed_brackets(char *line) {
    int length = strlen(line);
    for (int i = 0; i < length; ++i) {
        if ((i == 0 || i == 1 || i == length - 2 || i == length - 1) && line[i] != '<') {
            return -1;
        }
        if (i >= 2 && i <= length - 3 && line[i] == '<') {
            return -1;
        }
    }
    return 0;
}

//Passed JUnitTest!
string_list *get_args_if_correct(char **args) {
    string_list *arg_list = new_string_list();
    for (int j = 0; j < _msize(args) / 4; ++j) {
        if (is_word(args[j]) == -1) {
            perror("arg in declaration has invalid name!");
            exit(1);
        } else {
            add_in_string_list(arg_list, args[j]);
        }
    }
    return arg_list;
}

//FIXME: Make declaration list because you can create overloading =)
//Passed JUnitTest!
aio_declaration *get_declaration_of_method(char *method_name, string_list *source_code, int start_index) {
    int current_index = start_index - 1;
    char *input_line = get_string_in_list_by_index(source_code, current_index);
    char *current_line = trim(input_line);
    while (strcmp(current_line, "") != 0 && current_index >= 0) {
        char *declaration_prefix = "~dec:";
        int starts_as_declaration = starts_with_prefix(current_line, declaration_prefix);
        if (starts_as_declaration == 0) {
            //Remove declaration prefix:
            char *bracket_line = remove_prefix(current_line, declaration_prefix);
            //<<w+<<:
            if (strlen(bracket_line) > 4 && is_correct_placed_brackets(bracket_line) == 0) {
                //Remove brackets:
                char *left_padding = remove_prefix(bracket_line, "<<");
                char *right_padding = remove_suffix(left_padding, "<<");
                //Split naked args;
                char **dirty_split_args = split_by_string(right_padding, ",");
                //Trim all args:
                char **args = trim_all(dirty_split_args, _msize(dirty_split_args) / 4);
                string_list *arg_list = get_args_if_correct(args);
                aio_declaration *aio_declaration = new_aio_declaration(method_name, arg_list);
                return aio_declaration;
            } else {
                perror("invalid bracket placement in declaration!");
                exit(1);
            }
        } else {
            current_line = get_string_in_list_by_index(source_code, --current_index);
        }
    }
    return NULL;
}

//Passed JUnitTest!
int is_method_in_the_same_file(const char *expression) {
    int length = strlen(expression);
    //w+~
    if (length > 1) {
        if (isalpha(expression[0]) && expression[length - 1] == '~') {
            for (int i = 1; i < length - 1; ++i) {
                if (!isalnum(expression[i])) {
                    return -1;
                }
            }
            return 0;
        }
    }
    return -1;
}

//Passed JUnitTest!
int is_method_in_the_other_file(const char *expression) {
    int length = strlen(expression);
    //w+.@w+~
    if (length > 4) {
        //first is letter and ends with ~:
        if (isalpha(expression[0]) && expression[length - 1] == '~') {
            int was_delimiter = -1;
            int start_method_name_index = 0;
            for (int i = 1; i < length - 1; ++i) {
                //across with dot:
                if (expression[i] == '.') {
                    //.@w+
                    if (i + 2 < length - 1 && expression[i + 1] == '@') {
                        was_delimiter = 0;
                        start_method_name_index = i + 2;
                        break;
                    } else {
                        perror("illegal aio line with method invocation");
                        exit(1);
                    }
                } else if (!isalnum(expression[i])) {
                    return -1;
                }
            }
            if (was_delimiter == 0) {
                for (int i = start_method_name_index; i < length - 1; ++i) {
                    if (!isalnum(expression[i])) {
                        return -1;
                    }
                }
                return 0;
            } else {
                return -1;
            }
        }
    }
    return -1;
}

//Passed JUnitTest!
enum aio_method_size_type get_size_type_of_method(string_list *method_code) {
    if (method_code->size == 1) {
        char *trim_line = trim(method_code->strings[0]);
        if (is_method_in_the_same_file(trim_line) == 0
            || is_default_operations(trim_line) == 0
            || is_method_in_the_other_file(trim_line) == 0) {
            return THE_SHORTEST;
        } else {
            return SHORT;
        }
    }
    return DEFAULT;
}

//Passed JUnitTest!
aio_method_definition *build_aio_method_definition(char *method_name, string_list *source_code, int start_index) {
    //Create aio declaration:
    aio_declaration *declaration = get_declaration_of_method(method_name, source_code, start_index);
    //Create aio annotation list:
    aio_annotation_list *annotation_list = get_annotations_of_method(method_name, source_code, start_index);
    if (is_default_behaviour(core) == 0) {
        //Create string list of method code:
        string_list *method_code = get_source_code_of_method(method_name, source_code, start_index);
        //Set method size type:
        enum aio_method_size_type size_type = get_size_type_of_method(method_code);
        return new_aio_method_definition(method_name, declaration, annotation_list, method_code, size_type);
    } else {
        return NULL;
    }
}