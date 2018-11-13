//lang:
#include <aio_lang/aio_modifiers/aio_modifiers.h>
//runtime:
#include <aio_runtime/aio_ray/aio_ray.h>
#include <aio_runtime/aio_value/aio_value.h>
#include <aio_runtime/aio_result/aio_result.h>
#include <aio_parsing/aio_expression/aio_expression_parser.h>
#include <aio_runtime/aio_value/advanced_functions/cast_aio_value.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

#define AIO_DOUBLE_PARSER_DEBUG

#ifdef AIO_DOUBLE_PARSER_DEBUG

#endif

#define AIO_DOUBLE_PARSER_INFO_TAG "AIO_DOUBLE_PARSER_INFO"

#define AIO_DOUBLE_PARSER_ERROR_TAG "AIO_DOUBLE_PARSER_ERROR"

aio_value *aio_expression_parser::aio_double_parser::parse(
        const str_hook *expression_hook,
        aio_ray *control_graph
)
{
    const aio_result *result = aio_double_parser::make_plus_or_minus(expression_hook, control_graph);
    if (result->rest->is_not_empty()) {
        throw_error_with_tag(AIO_DOUBLE_PARSER_INFO_TAG, "Can not fully parse expression!");
    }
    const double result_double_acc = result->value->get.double_acc;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete result;
    //------------------------------------------------------------------------------------------------------------------
    return new_aio_double_value(result_double_acc);
}

aio_result *aio_expression_parser::aio_double_parser::make_plus_or_minus(
        const str_hook *expression_hook,
        aio_ray *control_graph
)
{
    const char* expression_string = expression_hook->get_string();
    const aio_result *left_result = make_multiplication_or_division(expression_hook, control_graph);
    aio_value *left_value = left_result->value;
    if (!left_value) {
        throw_error_with_str_hook(AIO_DOUBLE_PARSER_ERROR_TAG, "Found null in expression:", expression_hook);
    }
    str_hook *left_hook = new_str_hook_by_other(left_result->rest);
    double left_acc = left_value->get.double_acc;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_aio_result(left_result);
#ifdef AIO_DOUBLE_PARSER_DEBUG
    log_info_str_hook(AIO_DOUBLE_PARSER_INFO_TAG, "After left multiplication rest:", left_hook);
#endif
    while (is_not_empty_hooked_str(left_hook)) {
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
            aio_result *right_result = make_multiplication_or_division(next_hook, control_graph);
            aio_value *right_value = right_result->value;
            if (!right_value) {
                throw_error_with_hook(AIO_DOUBLE_PARSER_INFO_TAG, "Found null in expression", next_hook);
            }
#ifdef AIO_DOUBLE_PARSER_DEBUG
            log_info_str_hook(AIO_DOUBLE_PARSER_INFO_TAG, "After right multiplication rest:", right_result->rest);
#endif
            const double right_acc = right_value->get.double_acc;
            if (is_plus) {
                left_acc += right_acc;
#ifdef AIO_DOUBLE_PARSER_DEBUG
                log_info_double(AIO_DOUBLE_PARSER_INFO_TAG, "After plus acc:", left_acc);
#endif
            }
            if (is_minus) {
                left_acc -= right_acc;
#ifdef AIO_DOUBLE_PARSER_DEBUG
                log_info_double(AIO_DOUBLE_PARSER_INFO_TAG, "After minus acc:", left_acc);
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
    return new_aio_double_result(left_acc, rest);
}


static aio_result *make_double(const_str_hook *expression_hook)
{
    const_string expression_str = expression_hook->source_string;
    const int right_border = expression_hook->end;
    int i = expression_hook->start;
    while (!is_sign(expression_str[i]) && i < right_border) {
        i++;
    }
    str_hook *captured_element = new_str_hook(expression_str);
    captured_element->start = expression_hook->start;
    captured_element->end = i;
    double value = 0;
    if (is_null_hooked(captured_element)) {
        throw_error_with_hook(AIO_DOUBLE_PARSER_INFO_TAG, "Found null in expression:", expression_hook);
    } else
        //Maybe int value?
    if (is_int_hooked(captured_element)) {
        value = str_hook_to_int(captured_element);
    } else
        //Maybe double value?
    if (is_double_hooked(captured_element)) {
        value = str_hook_to_double(captured_element);
    } else
        //Maybe string value?
    if (is_string_hooked(captured_element)) {
        const_str_hook *naked_hook = lower_str_hook_quotes(captured_element);
#ifdef AIO_DOUBLE_PARSER_DEBUG
        log_info_str_hook(AIO_DOUBLE_PARSER_INFO_TAG, "Make double from string:", naked_hook);
#endif
        if (is_boolean_hooked(naked_hook)) {
            value = str_hook_to_boolean(naked_hook);
        } else if (is_int_hooked(naked_hook)) {
            value = str_hook_to_int(naked_hook);
        } else if (is_double_hooked(naked_hook)) {
            value = str_hook_to_double(naked_hook);
        } else {
            throw_error_with_tag(AIO_DOUBLE_PARSER_INFO_TAG, "Can not cast string to double!");
        }
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_const_str_hook(naked_hook);
    } else
        //Maybe boolean value?
    if (is_boolean_hooked(captured_element)) {
        value = str_hook_to_boolean(captured_element);
    } else {
        throw_error_with_tag(AIO_DOUBLE_PARSER_INFO_TAG, "Cannot define type of expression!");
    }
#ifdef AIO_DOUBLE_PARSER_DEBUG
    log_info_double(AIO_DOUBLE_PARSER_INFO_TAG, "Made double:", value);
#endif
    str_hook *rest_part = new_str_hook(expression_str);
    rest_part->start = i;
    rest_part->end = right_border;
#ifdef AIO_DOUBLE_PARSER_DEBUG
    log_info_str_hook(AIO_DOUBLE_PARSER_INFO_TAG, "After making double rest:", rest_part);
#endif
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_str_hook(captured_element);
    return new_aio_double_result(value, rest_part);
}

static aio_result *make_multiplication_or_division(
        const_str_hook *expression_hook,
        const_aio_function_control_graph *control_graph
)
{
#ifdef AIO_DOUBLE_PARSER_DEBUG
    log_info_str_hook(AIO_DOUBLE_PARSER_INFO_TAG, "Make multiplication or division", expression_hook);
#endif
    const_string expression_string = expression_hook->source_string;
    aio_result *left_result = make_parentheses(expression_hook, control_graph, cast_to_double, make_double);
    aio_value *left_value = left_result->value;
    if (!left_value) {
        throw_error_with_hook(AIO_DOUBLE_PARSER_INFO_TAG, "Found null in expression:", expression_hook);
    }
    str_hook *left_hook = new_str_hook_by_other(left_result->rest);
    double left_acc = left_value->get.double_acc;
#ifdef AIO_DOUBLE_PARSER_DEBUG
    log_info_str_hook(AIO_DOUBLE_PARSER_INFO_TAG, "After left parenthesis rest:", left_hook);
#endif
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_aio_result(left_result);
    while (is_not_empty_hooked_str(left_hook)) {
        const char symbol = expression_string[left_hook->start];
        //Check symbol:
        const_boolean is_multiply = is_multiply_sign(symbol);
        const_boolean is_division = is_division_sign(symbol);
        if (is_multiply || is_division) {
            //Create after sign part:
            str_hook *next_hook = new_str_hook(expression_string);
            next_hook->start = left_hook->start + 1;
            next_hook->end = left_hook->end;
            aio_result *right_result = make_parentheses(next_hook, control_graph, cast_to_double, make_double);
            aio_value *right_value = right_result->value;
            if (!right_value) {
                throw_error_with_hook(AIO_DOUBLE_PARSER_INFO_TAG, "Found null in expression:", next_hook);
            }
#ifdef AIO_DOUBLE_PARSER_DEBUG
            log_info_str_hook(AIO_DOUBLE_PARSER_INFO_TAG, "After right parenthesis rest:", right_result->rest);
#endif
            const double right_acc = right_value->get.double_acc;
            if (is_multiply) {
                left_acc *= right_acc;
#ifdef AIO_DOUBLE_PARSER_DEBUG
                log_info_double(AIO_DOUBLE_PARSER_INFO_TAG, "After multiplication acc:", left_acc);
#endif
            }
            if (is_division) {
                left_acc /= right_acc;
#ifdef AIO_DOUBLE_PARSER_DEBUG
                log_info_double(AIO_DOUBLE_PARSER_INFO_TAG, "After division acc:", left_acc);
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
    return new_aio_double_result(left_acc, rest);
}
