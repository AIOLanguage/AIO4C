#include "../../../../../headers/lib/utils/error_utils/error_utils.h"

#define AIO_TYPE_PARSER_TAG "AIO_TYPE_PARSER"

struct aio_value *parse_type_value_string(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
)
{
    throw_error_with_tag(AIO_TYPE_PARSER_TAG, "AIO core doesn't support custom types yet!");
}