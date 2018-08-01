#include <stdio.h>
#include "../../../headers/lang/types/aio_type.h"
#include "../../../headers/lang/object/aio_file.h"
#include "../../../headers/lang/methods/aio_method_container.h"
#include "../../../headers/lang/methods/aio_method.h"
#include "../../../headers/tools/parsers/aio_parser.h"

aio_str
parse_line_expression(aio_file *context, aio_method_definition *method_definition,
                      aio_method_container *method_container,
                      char *code_line) {
    char *result;
    //첫 단어는 "int"입니다.
    result = parse_in_line_expression(context, method_definition, method_container, code_line);
    //첫 단어는 "dou"입니다.
    result = parse_dou_line_expression(context, method_definition, method_container, code_line);
    //첫 단어는 "dou"입니다.
    result = parse_cha_line_expression(context, method_definition, method_container, code_line);
    //첫 단어는 "dou"입니다.
    result = parse_str_line_expression(context, method_definition, method_container, code_line);
}

aio_variable *get_variable_from_method_container(char *variable_name, aio_method_container *method_container) {
    if (contains_variable_in_map(variable_name, method_container->arg_map) == 0) {
        return get_aio_variable_in_map_by_name(method_container->arg_map, variable_name);
    }
    if (contains_variable_in_map(variable_name, method_container->variable_map) == 0) {
        return get_aio_variable_in_map_by_name(method_container->variable_map, variable_name);
    }
    perror("error: try get not exist variable!");
}