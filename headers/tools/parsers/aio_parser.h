#ifndef AIO_PARSER_H
#define AIO_PARSER_H

#include "../../lang/methods/aio_method_container.h"
#include "../../lang/object/aio_object.h"


//제목들:

aio_str parse_line_expression(aio_object *object, aio_method_definition *method_definition,
                              aio_method_container *method_container, char *code_line);

aio_str parse_in_line_expression(aio_object *object, aio_method_definition *method_definition,
                                 aio_method_container *method_container, char *code_line);

aio_str parse_dou_line_expression(aio_object *object, aio_method_definition *method_definition,
                                  aio_method_container *method_container, char *code_line);

aio_str parse_cha_line_expression(aio_object *object, aio_method_definition *method_definition,
                                  aio_method_container *method_container, char *code_line);

aio_str parse_str_line_expression(aio_object *object, aio_method_definition *method_definition,
                                  aio_method_container *method_container, char *code_line);

aio_variable *get_variable_from_method_container(char *variable_name, aio_method_container *method_container);

#endif //AIO_PARSER_H