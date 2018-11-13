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
    const char *expression_string = expression_hook->get_string();
    const aio_result *left_result = aio_double_parser::make_multiplication_or_division(expression_hook, control_graph);
    aio_value *left_value = left_result->value;
    if (!left_value) {
        throw_error_with_str_hook(AIO_DOUBLE_PARSER_ERROR_TAG, "Found null in expression:", expression_hook);
    }
    str_hook *left_hook = new str_hook(left_result->rest);
    double left_acc = left_value->get.double_acc;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete left_result;
    //------------------------------------------------------------------------------------------------------------------
    while (true) {
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
            aio_result *right_result = aio_double_parser::make_multiplication_or_division(next_hook, control_graph);
            aio_value *right_value = right_result->value;
            if (!right_value) {
                throw_error_with_str_hook(AIO_DOUBLE_PARSER_INFO_TAG, "Found null in expression", next_hook);
            }
            const double right_acc = right_value->get.double_acc;
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
    delete (left_hook);
    //------------------------------------------------------------------------------------------------------------------
    return new aio_result(left_acc, rest);
}

aio_result *aio_expression_parser::aio_double_parser::make_multiplication_or_division(
        const str_hook *expression_hook,
        aio_ray *control_graph
)
{
    const char *expression_string = expression_hook->get_string();
    aio_result *left_result = aio_expression_parser::aio_assistant::make_parentheses(
            expression_hook,
            control_graph,
            cast_to_double,
            aio_double_parser::make_double
    );
    aio_value *left_value = left_result->value;
    if (!left_value) {
        throw_error_with_str_hook(AIO_DOUBLE_PARSER_INFO_TAG, "Found null in expression:", expression_hook);
    }
    str_hook *left_hook = new str_hook(left_result->rest);
    double left_acc = left_value->get.double_acc;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete left_result;
    //------------------------------------------------------------------------------------------------------------------
    while (true) {
        const char symbol = expression_string[left_hook->start];
        //Check symbol:
        const bool is_multiply = is_multiply_sign(symbol);
        const bool is_division = is_division_sign(symbol);
        if (is_multiply || is_division) {
            //Create after sign part:
            str_hook *next_hook = new str_hook(expression_string);
            next_hook->start = left_hook->start + 1;
            next_hook->end = left_hook->end;
            aio_result *right_result = aio_assistant::make_parentheses(
                    next_hook,
                    control_graph,
                    cast_to_double,
                    make_double
            );
            aio_value *right_value = right_result->value;
            if (!right_value) {
                throw_error_with_str_hook(AIO_DOUBLE_PARSER_INFO_TAG, "Found null in expression:", next_hook);
            }
            const double right_acc = right_value->get.double_acc;
            if (is_multiply) {
                left_acc *= right_acc;
            }
            if (is_division) {
                left_acc /= right_acc;
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
    delete (left_hook);
    //------------------------------------------------------------------------------------------------------------------
    return new aio_result(left_acc, rest);
}

aio_result *aio_expression_parser::aio_double_parser::make_double(const str_hook *expression_hook)
{
    const char *expression_str = expression_hook->get_string();
    const unsigned right_border = expression_hook->end;
    unsigned i = expression_hook->start;
    while (!is_sign(expression_str[i]) && i < right_border) {
        i++;
    }
    str_hook *captured_element = new str_hook(expression_str);
    captured_element->start = expression_hook->start;
    captured_element->end = i;
    double value = 0;
    if (is_aio_null_modifier(captured_element)) {
        throw_error_with_str_hook(AIO_DOUBLE_PARSER_INFO_TAG, "Found null in expression:", expression_hook);
    } else
        //Maybe int value?
    if (captured_element->matches_int()) {
        value = captured_element->to_int();
    } else
        //Maybe double value?
    if (captured_element->matches_double()) {
        value = captured_element->to_double();
    } else
        //Maybe string value?
    if (captured_element->matches_string()) {
        const str_hook *naked_hook = captured_element->lower_quotes();
        if (naked_hook->matches_boolean()) {
            value = naked_hook->to_boolean();
        } else if (naked_hook->matches_int()) {
            value = naked_hook->to_int();
        } else if (naked_hook->matches_double()) {
            value = naked_hook->to_double();
        } else {
            throw_error_with_tag(AIO_DOUBLE_PARSER_INFO_TAG, "Can not cast string to double!");
        }
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        delete naked_hook;
        //--------------------------------------------------------------------------------------------------------------
    } else
        //Maybe boolean value?
    if (captured_element->matches_boolean()) {
        value = captured_element->to_boolean();
    } else {
        throw_error_with_tag(AIO_DOUBLE_PARSER_INFO_TAG, "Cannot define type of expression!");
    }
    str_hook *rest_part = new str_hook(expression_str);
    rest_part->start = i;
    rest_part->end = right_border;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete (captured_element);
    //------------------------------------------------------------------------------------------------------------------
    return new aio_result(value, rest_part);
}