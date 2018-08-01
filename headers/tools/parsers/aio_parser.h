#ifndef AIO_PARSER_H
#define AIO_PARSER_H


//제목들 (headers):

#include "../../lang/aio_method/aio_method_container.h"
#include "../../lang/aio_method/method_definition/aio_method_definition.h"
#include "../../lang/aio_context/aio_context.h"

string parse_line_expression(aio_context *context, aio_method_definition *method_definition,
                             aio_method_container *method_container, const_string code_line);

string parse_in_line_expression(aio_context *context, aio_method_definition *method_definition,
                                aio_method_container *method_container, const_string code_line);

string parse_dou_line_expression(aio_context *context, aio_method_definition *method_definition,
                                 aio_method_container *method_container, const_string code_line);

string parse_str_line_expression(aio_context *context, aio_method_definition *method_definition,
                                 aio_method_container *method_container, const_string code_line);

string parse_boo_line_expression(aio_context *context, aio_method_definition *method_definition,
                                 aio_method_container *method_container, const_string code_line);

aio_variable *get_variable_from_method_container(char *variable_name, aio_method_container *method_container);

#endif //AIO_PARSER_H