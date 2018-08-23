
#include "../../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../../../headers/lang/aio_function/aio_result/aio_result.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/lang/aio_context/aio_context.h"
#include "../../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"

#define AIO_DOUBLE_PARSER_DEBUG

#ifdef AIO_DOUBLE_PARSER_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

#define AIO_DOUBLE_PARSER_TAG "AIO_DOUBLE_PARSER"

/**
 * Business logic.
 */

static aio_result *make_double(const_str_hook *expression_hook)
{
    const_string expression_str = expression_hook->source_ref;
    const int right_border = expression_hook->end;
    int i = expression_hook->start;
    while (!is_sign(expression_str[i]) && i < right_border) {
        i++;
    }
    str_hook *captured_element = new_str_hook(expression_str);
    captured_element->start = expression_hook->start;
    captured_element->end = i;
    double value = 0;
    //Maybe int value?
    if (is_int_hooked(captured_element)) {
        value = str_hook_to_int(captured_element);
    }
    //Maybe double value?
    if (is_double_hooked(captured_element)) {
        value = str_hook_to_double(captured_element);
    }
    //Maybe string value?
    if (is_string_hooked(captured_element)) {
        const_str_hook *str_hook = lower_str_hook_quotes(captured_element);
        if (is_boolean_hooked(str_hook)) {
            value = str_hook_to_boolean(str_hook);
        } else {
            value = str_hook_to_double(str_hook);
        }
    }
    //Maybe boolean value?
    if (is_boolean_hooked(captured_element)) {
        value = str_hook_to_boolean(captured_element);
    } else {
        throw_error_with_tag(AIO_DOUBLE_PARSER_TAG, "Cannot define type of expression!");
    }
    str_hook *rest_part = new_str_hook(expression_str);
    rest_part->start = i;
    rest_part->end = right_border;
#ifdef AIO_DOUBLE_PARSER_DEBUG
    log_info_str_hook(AIO_DOUBLE_PARSER_TAG, "After making double rest:", rest_part);
#endif
    return new_aio_double_result(value, rest_part);
}

static aio_result *make_multiplication_or_division_or_mod(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    const_string expression_string = expression_hook->source_ref;
    aio_result *left_result = make_parentheses(expression_hook, context, control_graph, cast_to_double, make_double);
#ifdef AIO_DOUBLE_PARSER_DEBUG
    log_info_str_hook(AIO_DOUBLE_PARSER_TAG, "After left parenthesis rest:", left_result->rest);
#endif
    while (TRUE) {
        if (is_empty_hooked_str(left_result->rest)) {
            return left_result;
        }
        const char symbol = expression_string[left_result->rest->start];
        //Check symbol:
        const_boolean is_multiply = is_multiply_sign(symbol);
        const_boolean is_division = is_division_sign(symbol);
        if (is_multiply || is_division) {
            //Create after sign part:
            str_hook *next_hook = new_str_hook(expression_string);
            next_hook->start = left_result->rest->start + 1;
            next_hook->end = left_result->rest->end;
            aio_result *right_result = make_parentheses(next_hook, context, control_graph, cast_to_double, make_double);
#ifdef AIO_DOUBLE_PARSER_DEBUG
            log_info_str_hook(AIO_DOUBLE_PARSER_TAG, "After right parenthesis rest:", right_result->rest);
#endif
            const double right_acc = right_result->value->get.double_acc;
            if (is_multiply) {
                left_result->value->get.double_acc *= right_acc;
            }
            if (is_division) {
                left_result->value->get.double_acc /= right_acc;
            }
            left_result->rest = new_str_hook_by_other(right_result->rest);
        } else {
            return left_result;
        }
    }
}

static aio_result *make_plus_or_minus(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
)
{
    const_string expression_string = expression_hook->source_ref;
    aio_result *left_result = make_multiplication_or_division_or_mod(expression_hook, context, control_graph);
#ifdef AIO_DOUBLE_PARSER_DEBUG
    log_info_str_hook(AIO_DOUBLE_PARSER_TAG, "After left multiplication rest:", left_result->rest);
#endif
    double left_acc = left_result->value->get.double_acc;
    while (is_not_empty_hooked_str(left_result->rest)) {
        const char symbol = expression_string[left_result->rest->start];
        //Check symbol:
        const_boolean is_plus = is_plus_sign(symbol);
        const_boolean is_minus = is_minus_sign(symbol);
        if (is_plus || is_minus) {
            //Create after sign part:
            str_hook *next_hook = new_str_hook(expression_string);
            next_hook->start = left_result->rest->start + 1;
            next_hook->end = left_result->rest->end;
            //Find value after sign part:
            aio_result *right_result = make_multiplication_or_division_or_mod(next_hook, context, control_graph);
#ifdef AIO_DOUBLE_PARSER_DEBUG
            log_info_str_hook(AIO_DOUBLE_PARSER_TAG, "After right multiplication rest:", right_result->rest);
#endif
            const double right_acc = right_result->value->get.double_acc;
            if (is_plus) {
                left_acc += right_acc;
            }
            if (is_minus) {
                left_acc -= right_acc;
            }
            left_result = right_result;
        }
    }
    return new_aio_double_result(left_acc, new_str_hook_by_other(left_result->rest));
}

aio_value *parse_double_value_string(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    aio_result *result = make_plus_or_minus(expression_hook, context, control_graph);
    if (is_not_empty_hooked_str(result->rest)) {
        throw_error_with_tag(AIO_DOUBLE_PARSER_TAG, "Can not fully parse expression!");
    }
#ifdef AIO_DOUBLE_PARSER_DEBUG
    log_info_double(AIO_DOUBLE_PARSER_TAG, "Double parsing is complete:", result->value->get.double_acc);
#endif
    return new_aio_double_value(result->value->get.double_acc);
}