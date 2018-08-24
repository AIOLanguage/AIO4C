
#include "../../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../../headers/lang/aio_function/aio_result/aio_result.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lang/aio_context/aio_context.h"
#include "../../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"
#include "../../../../../headers/lib/utils/log_utils/log_utils.h"

#define AIO_INT_PARSER_DEBUG

#ifdef AIO_INT_PARSER_DEBUG

#endif

#define AIO_INT_PARSER_TAG "AIO_INT_PARSER"

/**
 * Business logic.
 */

static aio_result *make_int(const_str_hook *expression_hook)
{
#ifdef AIO_INT_PARSER_DEBUG
    log_info_str_hook(AIO_INT_PARSER_TAG, "Make int for expression", expression_hook);
#endif
    const_string expression_str = expression_hook->source_ref;
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
    //Maybe int value?
    if (is_int_hooked(captured_element)) {
        value = str_hook_to_int(captured_element);
    } else
        //Maybe double value?
    if (is_double_hooked(captured_element)) {
        const double d = str_hook_to_double(captured_element);
#ifdef AIO_INT_PARSER_DEBUG
        log_info_double(AIO_INT_PARSER_TAG, "Get double:", d);
#endif
        value = (int) d;
    } else
        //Maybe string value?
    if (is_string_hooked(captured_element)) {
        const_str_hook *str_hook = lower_str_hook_quotes(captured_element);
        if (is_boolean_hooked(str_hook)) {
            value = str_hook_to_boolean(str_hook);
        } else {
            value = str_hook_to_int(str_hook);
        }
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
    str_hook *rest_part = new_str_hook(expression_str);
    rest_part->start = i;
    rest_part->end = right_border;
#ifdef AIO_INT_PARSER_DEBUG
    log_info_str_hook(AIO_INT_PARSER_TAG, "Rest after int making:", rest_part);
#endif
    return new_aio_int_result(value, rest_part);
}

static aio_result *make_multiplication_or_division_or_mod(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
#ifdef AIO_INT_PARSER_DEBUG
    log_info_str_hook(AIO_INT_PARSER_TAG, "Make multiplication or division or mod for", expression_hook);
#endif
    const_string expression_string = expression_hook->source_ref;
    aio_result *left_result = make_parentheses(expression_hook, context, control_graph, cast_to_int, make_int);
    str_hook *left_hook = new_str_hook_by_other(left_result->rest);
    int left_acc = left_result->value->get.int_acc;
#ifdef AIO_INT_PARSER_DEBUG
    log_info_str_hook(AIO_INT_PARSER_TAG, "After left parenthesis rest:", left_hook);
#endif
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_aio_result(left_result);
    while (TRUE) {
        const char symbol = expression_string[left_hook->start];
        //Check symbol:
        const_boolean is_multiply = is_multiply_sign(symbol);
        const_boolean is_division = is_division_sign(symbol);
        const_boolean is_mod = is_mod_sign(symbol);
        if (is_multiply || is_division || is_mod) {
            //Create after sign part:
            str_hook *next_hook = new_str_hook(expression_string);
            next_hook->start = left_hook->start + 1;
            next_hook->end = left_hook->end;
            aio_result *right_result = make_parentheses(next_hook, context, control_graph, cast_to_int, make_int);
#ifdef AIO_INT_PARSER_DEBUG
            log_info_str_hook(AIO_INT_PARSER_TAG, "After right parenthesis rest:", right_result->rest);
#endif
            const int right_acc = right_result->value->get.int_acc;
            if (is_multiply) {
                left_acc *= right_acc;
#ifdef AIO_INT_PARSER_DEBUG
                log_info_int(AIO_INT_PARSER_TAG, "After multiplication acc:", left_acc);
#endif
            }
            if (is_division) {
                left_acc /= right_acc;
#ifdef AIO_INT_PARSER_DEBUG
                log_info_int(AIO_INT_PARSER_TAG, "After division acc:", left_acc);
#endif
            }
            if (is_mod) {
                left_acc %= right_acc;
#ifdef AIO_INT_PARSER_DEBUG
                log_info_int(AIO_INT_PARSER_TAG, "After mod acc:", left_acc);
#endif
            }
            const_str_hook *old_left_hook = left_hook;
            left_hook = new_str_hook_by_other(right_result->rest);
            //----------------------------------------------------------------------------------------------------------
            //찌꺼기 수집기 (Garbage collector):
            free_str_hook(next_hook);
            free_aio_result(right_result);
            free_const_str_hook(old_left_hook);
        } else {
            break;
        }
    }
    str_hook *rest = new_str_hook_by_other(left_hook);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_str_hook(left_hook);
    return new_aio_int_result(left_acc, rest);
}

static aio_result *make_plus_or_minus(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
#ifdef AIO_INT_PARSER_DEBUG
    log_info_str_hook(AIO_INT_PARSER_TAG, "Make plus or minus for:", expression_hook);
#endif
    const_string expression_string = expression_hook->source_ref;
    aio_result *left_result = make_multiplication_or_division_or_mod(expression_hook, context, control_graph);
    int left_acc = left_result->value->get.int_acc;
    str_hook *left_hook = new_str_hook_by_other(left_result->rest);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_aio_result(left_result);
#ifdef AIO_INT_PARSER_DEBUG
    log_info_str_hook(AIO_INT_PARSER_TAG, "After left multiplication rest:", left_hook);
#endif
    while (TRUE) {
        const char symbol = expression_string[left_hook->start];
        //Check symbol:
        const_boolean is_plus = is_plus_sign(symbol);
        const_boolean is_minus = is_minus_sign(symbol);
        if (is_plus || is_minus) {
            //Create after sign part:
            str_hook *next_hook = new_str_hook(expression_string);
            next_hook->start = left_hook->start + 1;
            next_hook->end = left_hook->end;
            //Find value after sign part:
            aio_result *right_result = make_multiplication_or_division_or_mod(next_hook, context, control_graph);
#ifdef AIO_INT_PARSER_DEBUG
            log_info_str_hook(AIO_INT_PARSER_TAG, "After right multiplication rest:", right_result->rest);
#endif
            const int right_acc = right_result->value->get.int_acc;
            if (is_plus) {
                left_acc += right_acc;
#ifdef AIO_INT_PARSER_DEBUG
                log_info_int(AIO_INT_PARSER_TAG, "After plus acc:", left_acc);
#endif
            }
            if (is_minus) {
                left_acc -= right_acc;
#ifdef AIO_INT_PARSER_DEBUG
                log_info_int(AIO_INT_PARSER_TAG, "After minus acc:", left_acc);
#endif
            }
            const_str_hook *old_left_hook = left_hook;
            left_hook = new_str_hook_by_other(right_result->rest);
            //----------------------------------------------------------------------------------------------------------
            //찌꺼기 수집기 (Garbage collector):
            free_str_hook(next_hook);
            free_aio_result(right_result);
            free_const_str_hook(old_left_hook);
        } else {
            break;
        }
    }
    str_hook *rest = new_str_hook_by_other(left_hook);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_str_hook(left_hook);
    return new_aio_int_result(left_acc, rest);
}

aio_value *parse_int_value_string(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    aio_result *result = make_plus_or_minus(expression_hook, context, control_graph);
    if (is_not_empty_hooked_str(result->rest)) {
        throw_error_with_tag(AIO_INT_PARSER_TAG, "Can not fully parse expression!");
    }
#ifdef AIO_INT_PARSER_DEBUG
    log_info_int(AIO_INT_PARSER_TAG, "Int parsing is complete", result->value->get.int_acc);
#endif
    return new_aio_int_value(result->value->get.int_acc);
}