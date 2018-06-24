#ifndef AIO_PARSER_H
#define AIO_PARSER_H

#include "../../lang/methods/AIOMethodContainer.h"
#include "../../lang/object/AIOObject.h"

aio_str
parse_line_expression(aio_object *object, aio_method_definition *methodDefinition,
                      aio_method_container *methodContainer,
                      char *codeLine);

//제목들:

aio_str
parseIntLineExpression(aio_object *object, aio_method_definition *methodDefinition, aio_method_container *methodContainer,
                       char *codeLine);

aio_str
parseDouLineExpression(aio_object *object, aio_method_definition *methodDefinition, aio_method_container *methodContainer,
                       char *codeLine);

aio_str
parseChaLineExpression(aio_object *object, aio_method_definition *methodDefinition, aio_method_container *methodContainer,
                       char *codeLine);

aio_str
parseStrLineExpression(aio_object *object, aio_method_definition *methodDefinition, aio_method_container *methodContainer,
                       char *codeLine);

aio_variable *getVariable(char *variableName, aio_method_container *methodContainer);

#endif //AIO_PARSER_H