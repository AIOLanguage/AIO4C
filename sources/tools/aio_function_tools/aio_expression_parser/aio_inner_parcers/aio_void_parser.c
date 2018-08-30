#include <mem.h>
#include <lang/aio_function/aio_result/aio_result.h>
#include <lib/utils/str_hook/str_hook.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <lang/aio_function/aio_value/aio_value.h>
#include <tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h>
#include <tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h>

#define AIO_VOID_PARSER_DEBUG

#define AIO_VOID_PARSER_TAG "AIO_VOID_PARSER"

#ifdef AIO_VOID_PARSER_DEBUG

#endif

static aio_result *make_null(const_str_hook *expression_hook)
{
    if (is_null_hooked(expression_hook)) {
        str_hook *empty_rest_hook = new_str_hook(expression_hook->source_string);
        return new_aio_result(NULL, empty_rest_hook);
    }
    throw_error_with_hook(AIO_VOID_PARSER_TAG, "Can not parse void expression!", expression_hook);
}

/**
 * Expects only one element of expression.
 */

aio_value *parse_void_value_string(
        const_str_hook *expression_hook,
        const_aio_function_control_graph *control_graph
)
{
    aio_result *result = make_function_or_variable(expression_hook, control_graph, cast_to_void, make_null);
    if (is_not_empty_hooked_str(result->rest)) {
        throw_error_with_hook(AIO_VOID_PARSER_TAG, "Can not parse void expression!", expression_hook);
    }
    aio_value *result_value = cast_to_void(result->value);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_aio_result(result);
    return result_value;
}