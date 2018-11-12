#include <lang/aio_function/aio_result/aio_result.h>
#include <lib/utils/str_hook/str_hook.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <lib/utils/string_utils/string_utils.h>
#include <lib/utils/char_utils/char_utils.h>
#include <lib/utils/error_utils/error_utils.h>
#include <tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h>
#include <lang/aio_function/aio_value/aio_value.h>
#include <tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h>

#define AIO_INT_PARSER_DEBUG

#ifdef AIO_INT_PARSER_DEBUG

#include <lib/utils/log_utils/log_utils.h>

#endif

#define AIO_INT_PARSER_TAG "AIO_INT_PARSER"

static aio_result *make_int(const_str_hook *expression_hook)
{
#ifdef AIO_INT_PARSER_DEBUG
    log_info_str_hook(AIO_INT_PARSER_TAG, "Make int for expression", expression_hook);
#endif
    const_string expression_str = expression_hook->source_string;
    const int right_border = expression_hook->end;
    int i = expression_hook->start;
    while (i < right_border) {
        const char symbol = expression_str[i];
        if (!is_sign(symbol)) {
            i++;
        } else {
            break;
        }
    }
    str_hook *captured_element = new_str_hook(expression_str);
    captured_element->start = expression_hook->start;
    captured_element->end = i;
#ifdef AIO_INT_PARSER_DEBUG
    log_info_str_hook(AIO_INT_PARSER_TAG, "Captured element:", captured_element);
#endif
    int value = 0;
    if (is_null_hooked(captured_element)) {
        throw_error_with_hook(AIO_INT_PARSER_TAG, "Found null in expression:", expression_hook);
    } else
        //Maybe int value?
    if (is_int_hooked(captured_element)) {
        value = str_hook_to_int(captured_element);
    } else
        //Maybe double value?
    if (is_double_hooked(captured_element)) {
        const double double_value = str_hook_to_double(captured_element);
#ifdef AIO_INT_PARSER_DEBUG
        log_info_double(AIO_INT_PARSER_TAG, "Get double:", double_value);
#endif
        value = (int) double_value;
    } else
        //Maybe string value?
    if (is_string_hooked(captured_element)) {
        const_str_hook *naked_hook = lower_str_hook_quotes(captured_element);
        if (is_boolean_hooked(naked_hook)) {
            value = str_hook_to_boolean(naked_hook);
        } else if (is_double_hooked(naked_hook)) {
            value = (int) str_hook_to_double(naked_hook);
        } else if (is_int_hooked(naked_hook)) {
            value = str_hook_to_int(naked_hook);
        }
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_const_str_hook(naked_hook);
    } else
        //Maybe boolean value?
    if (is_boolean_hooked(captured_element)) {
        value = str_hook_to_boolean(captured_element);
    } else {
        throw_error_with_tag(AIO_INT_PARSER_TAG, "Cannot define type of expression!");
    }
#ifdef AIO_INT_PARSER_DEBUG
    log_info_int(AIO_INT_PARSER_TAG, "Made int:", value);
#endif
    //Init after operation hook:
    str_hook *rest_part = new_str_hook(expression_str);
    rest_part->start = i;
    rest_part->end = right_border;
#ifdef AIO_INT_PARSER_DEBUG
    log_info_str_hook(AIO_INT_PARSER_TAG, "Rest after int making:", rest_part);
#endif
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_str_hook(captured_element);
    return new_aio_int_result(value, rest_part);
}