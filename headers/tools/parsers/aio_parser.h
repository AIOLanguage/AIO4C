#ifndef AIO_PARSER_H
#define AIO_PARSER_H

//제목들 (headers):

#include "../../lang/aio_context/aio_context.h"
#include "../../lang/aio_function/aio_function.h"

string parse_line_expression(aio_context *context, aio_function_definition *function_definition,
                             aio_function *function, const_string code_line);

string parse_in_line_expression(aio_context *context, aio_function_definition *function_definition,
                                aio_function *function, const_string code_line);

string parse_dou_line_expression(aio_context *context, aio_function_definition *function_definition,
                                 aio_function *function, const_string code_line);

string parse_str_line_expression(aio_context *context, aio_function_definition *function_definition,
                                 aio_function *function, const_string code_line);

string parse_boo_line_expression(aio_context *context, aio_function_definition *function_definition,
                                 aio_function *function, const_string code_line);

aio_variable *get_variable_from_function(char *variable_name, aio_function *function);

#endif //AIO_PARSER_H