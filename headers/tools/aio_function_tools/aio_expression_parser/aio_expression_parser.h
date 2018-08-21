#ifndef AIO_AIO_EXPRESSION_PARSER_H
#define AIO_AIO_EXPRESSION_PARSER_H

#include "../../../lang/aio_function/aio_value/aio_value.h"
#include "../../../lang/aio_context/aio_context.h"

aio_value *parse_value_string(const_string expression_string, const_aio_context *context);

#endif //AIO_AIO_EXPRESSION_PARSER_H