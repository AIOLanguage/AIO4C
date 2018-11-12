//runtime:
#include <aio_runtime/aio_ray/aio_ray.h>
#include <aio_runtime/aio_value/aio_value.h>
#include <aio_runtime/aio_result/aio_result.h>
#include <aio_parsing/aio_expression/aio_expression_parser.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define AIO_INT_PARSER_DEBUG

#ifdef AIO_INT_PARSER_DEBUG

#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>
#include <aio_runtime/aio_value/advanced_functions/cast_aio_value.h>
#include <aio_lang/aio_modifiers/aio_modifiers.h>
#include <aio_parsing/aio_expression/util/aio_type_matcher.h>

#endif

#define AIO_INT_PARSER_TAG "AIO_INT_PARSER"

aio_value *aio_expression_parser::aio_int_parser::parse(const str_hook *expression, aio_ray *ray)
{
    const aio_result *result = make_plus_or_minus(expression, ray);
    if (result->rest->is_not_empty()) {
        throw_error_with_tag(AIO_INT_PARSER_TAG, "Can not fully parse expression!");
    }
    const int result_int_acc = result->value->get.int_acc;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete result;
    //------------------------------------------------------------------------------------------------------------------
    return new_aio_int_value(result_int_acc);
}

aio_result *aio_expression_parser::aio_int_parser::make_plus_or_minus(const str_hook *expression, aio_ray *ray)
{
    const char *expression_string = expression->get_string();
    const aio_result *left_result = aio_int_parser::make_multiplication_or_division_or_mod(expression, ray);
    const aio_value *left_value = left_result->value;
    if (!left_value) {
        throw_error_with_str_hook(AIO_INT_PARSER_TAG, "Found null in expression:", expression);
    }
    int left_acc = left_value->get.int_acc;
    str_hook *left_hook = new str_hook(left_result->rest);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete left_result;
    //------------------------------------------------------------------------------------------------------------------
    while (left_hook->is_not_empty()) {
        const char symbol = expression_string[left_hook->start];
        //Check symbol:
        const bool is_plus = is_plus_sign(symbol);
        const bool is_minus = is_minus_sign(symbol);
        if (is_plus || is_minus) {
            //Create after sign part:
            str_hook *next_hook = new str_hook(expression_string);
            next_hook->start = left_hook->start + 1;
            next_hook->end = left_hook->end;
            //Find value after sign part:
            const aio_result *right_result = aio_int_parser::make_multiplication_or_division_or_mod(next_hook, ray);
            const aio_value *right_value = right_result->value;
            if (!right_value) {
                throw_error_with_str_hook(AIO_INT_PARSER_TAG, "Found null in expression:", next_hook);
            }
            const int right_acc = right_result->value->get.int_acc;
            if (is_plus) {
                left_acc += right_acc;
            }
            if (is_minus) {
                left_acc -= right_acc;
            }
            const str_hook *old_left_hook = left_hook;
            left_hook = new str_hook(right_result->rest);
            //----------------------------------------------------------------------------------------------------------
            //찌꺼기 수집기 (Garbage collector):
            delete next_hook;
            delete right_result;
            delete old_left_hook;
            //----------------------------------------------------------------------------------------------------------
        } else {
            break;
        }
    }
    str_hook *rest = new str_hook(left_hook);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete left_hook;
    //------------------------------------------------------------------------------------------------------------------
    return new aio_result(left_acc, rest);
}

aio_result *aio_expression_parser::aio_int_parser::make_multiplication_or_division_or_mod(
        const str_hook *expression,
        aio_ray *ray
)
{
    const char *expression_string = expression->get_string();
    const aio_result *left_result = make_parentheses(expression, ray, cast_to_int, make_int);
    const aio_value *left_value = left_result->value;
    if (!left_value) {
        throw_error_with_str_hook(AIO_INT_PARSER_TAG, "Found null in expression:", expression);
    }
    str_hook *left_hook = new str_hook(left_result->rest);
    int left_acc = left_result->value->get.int_acc;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete left_result;
    //------------------------------------------------------------------------------------------------------------------
    while (left_hook->is_not_empty()) {
        const char symbol = expression_string[left_hook->start];
        //Check symbol:
        const bool is_multiply = is_multiply_sign(symbol);
        const bool is_division = is_division_sign(symbol);
        const bool is_mod = is_mod_sign(symbol);
        if (is_multiply || is_division || is_mod) {
            //Create after sign part:
            str_hook *next_hook = new str_hook(expression_string);
            next_hook->start = left_hook->start + 1;
            next_hook->end = left_hook->end;
            const aio_result *right_result = make_parentheses(next_hook, ray, cast_to_int, make_int);
            const aio_value *right_value = right_result->value;
            if (!right_value) {
                throw_error_with_str_hook(AIO_INT_PARSER_TAG, "Found null in expression:", next_hook);
            }
            const int right_acc = right_result->value->get.int_acc;
            if (is_multiply) {
                left_acc *= right_acc;
            }
            if (is_division) {
                left_acc /= right_acc;
            }
            if (is_mod) {
                left_acc %= right_acc;
            }
            const str_hook *old_left_hook = left_hook;
            left_hook = new str_hook(right_result->rest);
            //----------------------------------------------------------------------------------------------------------
            //찌꺼기 수집기 (Garbage collector):
            delete next_hook;
            delete right_result;
            delete old_left_hook;
            //----------------------------------------------------------------------------------------------------------
        } else {
            break;
        }
    }
    str_hook *rest = new str_hook(left_hook);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete left_hook;
    //----------------------------------------------------------------------------------------------------------
    return new aio_result(left_acc, rest);
}

aio_result *aio_expression_parser::aio_int_parser::make_int(const str_hook *expression_hook)
{
    const char *expression_str = expression_hook->get_string();
    const int right_border = expression_hook->end;
    unsigned i = expression_hook->start;
    while (i < right_border) {
        const char symbol = expression_str[i];
        if (!is_sign(symbol)) {
            i++;
        } else {
            break;
        }
    }
    str_hook *captured_element = new str_hook(expression_str);
    captured_element->start = expression_hook->start;
    captured_element->end = i;
    int value = 0;
    if (is_aio_null_modifier(captured_element)) {
        throw_error_with_str_hook(AIO_INT_PARSER_TAG, "Found null in expression:", expression_hook);
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