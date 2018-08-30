#include <lang/aio_function/aio_value/aio_value.h>
#include <lib/utils/str_hook/str_hook.h>
#include <tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h>
#include <lib/utils/error_utils/error_utils.h>

#define AIO_TYPE_PARSER_TAG "AIO_TYPE_PARSER"

aio_value *parse_type_value_string(
        const_str_hook *expression_hook,
        const_aio_function_control_graph *control_graph
)
{
    throw_error_with_tag(
            AIO_TYPE_PARSER_TAG,
            "AIO core doesn't support custom types yet!\nSorry this is only development version"
    );
}