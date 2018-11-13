//lang:
#include <aio_lang/aio_modifiers/aio_modifiers.h>
//parsing:
#include <aio_parsing/aio_expression/aio_expression_parser.h>
//runtime:
#include <aio_runtime/aio_value/aio_value.h>
#include <aio_runtime/aio_result/aio_result.h>
#include <aio_runtime/aio_value/advanced_functions/cast_aio_value.h>
//lib4aio:
#include <lib4aio_cpp_headers/aio_explorer/aio_explorer.h>
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/point_watcher/point_watcher.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <aio_runtime/aio_value/advanced_functions/compare_aio_value.h>
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

#define AIO_BOOLEAN_PARSER_INFO_TAG "AIO_BOOLEAN_PARSER_INFO"

#define AIO_BOOLEAN_PARSER_ERROR_TAG "AIO_BOOLEAN_PARSER_ERROR"

#define AIO_BOOLEAN_PARSER_DEBUG

#ifdef AIO_BOOLEAN_PARSER_DEBUG

#endif

aio_value *aio_expression_parser::aio_boolean_parser::parse(
        const str_hook *expression_hook,
        aio_ray *control_graph
)
{
    const aio_result *result = aio_boolean_parser::make_or(expression_hook, control_graph);
    if (result->rest->is_not_empty()) {
        throw_error_with_tag(AIO_BOOLEAN_PARSER_INFO_TAG, "Can not fully parse expression!");
    }
    const bool result_boolean_acc = result->value->get.boolean_acc;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete result;
    //------------------------------------------------------------------------------------------------------------------
    return new_aio_boolean_value(result_boolean_acc);
}

aio_result *aio_expression_parser::aio_boolean_parser::make_or(
        const str_hook *expression_hook,
        aio_ray *control_graph
)
{
    const char *expression_string = expression_hook->get_string();
    const aio_result *left_result = aio_boolean_parser::make_and(expression_hook, control_graph);
    const aio_value *left_value = left_result->value;
    if (!left_value) {
        throw_error_with_str_hook(AIO_BOOLEAN_PARSER_INFO_TAG, "Found null in expression:", expression_hook);
    }
    str_hook *left_hook = new str_hook(left_result->rest);
    bool left_acc = left_value->get.boolean_acc;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete left_result;
    while (true) {
        const char symbol = expression_string[left_hook->start];
        if (is_or_sign(symbol)) {
            //Create after sign part:
            str_hook *next_hook = new str_hook(expression_string);
            next_hook->start = left_hook->start + 1;
            next_hook->end = left_hook->end;
            //Find value after sign part:
            aio_result *right_result = make_and(next_hook, control_graph);
            aio_value *right_value = right_result->value;
            if (!right_value) {
                throw_error_with_str_hook(AIO_BOOLEAN_PARSER_INFO_TAG, "Found null in expression:", next_hook);
            }
            const bool right_acc = right_result->value->get.boolean_acc;
            left_acc = left_acc || right_acc;
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

aio_result *aio_expression_parser::aio_boolean_parser::make_and(
        const str_hook *expression_hook,
        aio_ray *control_graph
)
{
    const char *expression_string = expression_hook->get_string();
    aio_result *left_result = aio_boolean_parser::make_boolean_parentheses(expression_hook, control_graph);
    aio_value *left_value = left_result->value;
    if (!left_value) {
        throw_error_with_str_hook(AIO_BOOLEAN_PARSER_INFO_TAG, "Found null in expression:", expression_hook);
    }
    str_hook *left_hook = new str_hook(left_result->rest);
    bool left_acc = left_value->get.boolean_acc;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete left_result;
    while (true) {
        const char symbol = expression_string[left_hook->start];
        if (is_and_sign(symbol)) {
            //Create after sign part:
            str_hook *next_hook = new str_hook(expression_string);
            next_hook->start = left_hook->start + 1;
            next_hook->end = left_hook->end;
            aio_result *right_result = aio_boolean_parser::make_boolean_parentheses(next_hook, control_graph);
            aio_value *right_value = right_result->value;
            if (!right_value) {
                throw_error_with_str_hook(AIO_BOOLEAN_PARSER_INFO_TAG, "Found null in expression:", next_hook);
            }
            const bool right_acc = right_value->get.boolean_acc;
            left_acc = left_acc && right_acc;
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

aio_result *aio_expression_parser::aio_boolean_parser::make_boolean_parentheses(
        const str_hook *expression_hook,
        aio_ray *control_graph
)
{
    const char *expression_str = expression_hook->get_string();
    const char first_symbol = expression_str[expression_hook->start];
    if (is_opening_parenthesis(first_symbol)) {
        //Prepare to explore parenthesis bounds:
        const unsigned start_parenthesis = expression_hook->start;
        //Create inner expression hook:
        str_hook *in_parenthesis_hook = aio_explorer::explore_hook_scope(start_parenthesis, '(', ')', expression_hook);
        const char next_symbol_after_parenthesis = expression_str[in_parenthesis_hook->end + 1];
        if (is_and_sign(next_symbol_after_parenthesis)|| is_or_sign(next_symbol_after_parenthesis)) {
#ifdef AIO_BOOLEAN_PARSER_DEBUG
            log_info_str_hook(AIO_BOOLEAN_PARSER_INFO_TAG, "IN PARENTHESIS HOOK:", in_parenthesis_hook);
#endif
            //Get value into parenthesis:
            aio_value *in_parenthesis_value = aio_expression_parser::parse(in_parenthesis_hook, control_graph);
            //Cast to string:
            aio_value *value = cast_to_boolean(in_parenthesis_value);
            //Create next rest:
            str_hook *next_hook = new str_hook(expression_str);
            next_hook->start = in_parenthesis_hook->end;
            next_hook->end = expression_hook->end;
            //Create result:
            aio_result *in_parenthesis_result = new aio_result(value, next_hook);
            return in_parenthesis_result;
        }
        //--------------------------------------------------------------------------------------------------------------
        delete in_parenthesis_hook;
        //--------------------------------------------------------------------------------------------------------------
    }
    return aio_boolean_parser::make_condition(expression_hook, control_graph);
}

enum sign {
    SIGN_UNDEFINED, SIGN_EQUALS, SIGN_NOT_EQUALS, SIGN_MORE, SIGN_LESS, SIGN_MORE_OR_EQUALS, SIGN_LESS_OR_EQUALS
};

static aio_result *try_to_get_sign_condition(
        const str_hook *expression_hook,
        aio_ray *control_graph
)
{
    const char *expression_str = expression_hook->get_string();
    const unsigned start_position = expression_hook->start;
    const unsigned right_border = expression_hook->end;
    unsigned i = start_position;
    point_watcher *sign_watcher = new point_watcher();
    enum sign sign_type = SIGN_UNDEFINED;
    //Find left part of sign condition:
    while (i < right_border) {
        const char symbol = expression_str[i];
        //Check symbol:
        const bool is_equal = is_equal_sign((symbol));
        const bool is_more = is_more_sign(symbol);
        const bool is_less = is_less_sign(symbol);
        const bool is_not_equal = is_exclamation_point(symbol);
        if ((is_equal || is_less || is_more || is_not_equal) && sign_watcher->pointer == 0) {
            if (is_equal) {
                sign_type = SIGN_EQUALS;
            }
            if (is_less) {
                sign_type = SIGN_LESS;
            }
            if (is_more) {
                sign_type = SIGN_MORE;
            }
            if (is_not_equal) {
                sign_type = SIGN_NOT_EQUALS;
            }
            sign_watcher->mode = point_watcher::POINT_WATCHER_ACTIVE_MODE;
            break;
        }
        if (is_opening_parenthesis(symbol)) {
            sign_watcher->pointer++;
        }
        if (is_closing_parenthesis(symbol)) {
            sign_watcher->pointer--;
            if (sign_watcher->pointer < 0) {
                throw_error_with_tag(AIO_BOOLEAN_PARSER_ERROR_TAG, "Invalid parenthesis placement!");
            }
        }
        i++;
    }
    //If not found:
    if (sign_watcher->mode != point_watcher::POINT_WATCHER_ACTIVE_MODE) {
        return nullptr;
    }
    //Parse left expression:
    const str_hook *left_expression = new str_hook(expression_str, start_position, i);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_INFO_TAG, "LEFTTTTT", left_expression);
#endif
    aio_value *left_value = aio_expression_parser::parse(left_expression, control_graph);
    //Uniquely define sign & start right expression position:
    unsigned start_right_expr_pos = i + 1;
    const bool is_next_equal_sign = is_equal_sign(expression_str[i + 1]);
    if (sign_type == SIGN_EQUALS) {
        if (is_next_equal_sign) {
            start_right_expr_pos++;
        } else {
            throw_error_with_tag(AIO_BOOLEAN_PARSER_ERROR_TAG, "Invalid equal sign in condition");
        }
    }
    if (sign_type == SIGN_LESS) {
        if (is_next_equal_sign) {
            sign_type = SIGN_LESS_OR_EQUALS;
            start_right_expr_pos++;
        }
    }
    if (sign_type == SIGN_MORE) {
        if (is_next_equal_sign) {
            sign_type = SIGN_MORE_OR_EQUALS;
            start_right_expr_pos++;
        }
    }
    if (sign_type == SIGN_NOT_EQUALS) {
        if (is_next_equal_sign) {
            start_right_expr_pos++;
        } else {
            throw_error_with_tag(AIO_BOOLEAN_PARSER_ERROR_TAG, "Invalid equal sign in condition");
        }
    }
    //Find right part:
    unsigned end_right_expr_pos = start_right_expr_pos;
    while (end_right_expr_pos < right_border) {
        const char symbol = expression_str[end_right_expr_pos];
        //Check symbol:
        const bool is_and = is_and_sign(symbol);
        const bool is_or = is_or_sign(symbol);
        if ((is_and || is_or) && sign_watcher->pointer == 0) {
            break;
        }
        if (is_opening_parenthesis(symbol)) {
            sign_watcher->pointer++;
        }
        if (is_closing_parenthesis(symbol)) {
            sign_watcher->pointer--;
            if (sign_watcher->pointer < 0) {
                throw_error_with_tag(AIO_BOOLEAN_PARSER_ERROR_TAG, "Invalid parenthesis placement!");
            }
        }
        //Shift right end border for right expression:
        end_right_expr_pos++;
    }
    const str_hook *right_expression = new str_hook(
            expression_str,
            start_right_expr_pos,
            end_right_expr_pos
    );
    aio_value *right_value = aio_expression_parser::parse(right_expression, control_graph);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_INFO_TAG, "RIGHTTTT", right_expression);
#endif
    //Compare values:
    bool condition_value = false;
    switch (sign_type) {
        case SIGN_EQUALS:
            condition_value = are_equal_aio_values(left_value, right_value);
            break;
        case SIGN_NOT_EQUALS:
            condition_value = are_not_equal_aio_values(left_value, right_value);
            break;
        case SIGN_MORE:
            condition_value = is_more_aio_value_then_other(left_value, right_value);
            break;
        case SIGN_LESS:
            condition_value = is_less_aio_value_then_other(left_value, right_value);
            break;
        case SIGN_MORE_OR_EQUALS:
            condition_value = is_more_or_equals_aio_value_then_other(left_value, right_value);
            break;
        case SIGN_LESS_OR_EQUALS:
            condition_value = is_less_or_equals_aio_value_then_other(left_value, right_value);
            break;
        case SIGN_UNDEFINED:
            throw_error_with_tag(AIO_BOOLEAN_PARSER_INFO_TAG, "Invalid case!");
    }
    //Create next rest:
    str_hook *next_rest = new str_hook(expression_str, end_right_expr_pos, right_border);
    return new aio_result(condition_value, next_rest);
}

aio_result *aio_expression_parser::aio_boolean_parser::make_condition(
        const str_hook *expression_hook,
        aio_ray *control_graph
)
{
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info(AIO_BOOLEAN_PARSER_INFO_TAG, "MAKE CONDITION!!!");
#endif
    aio_result *sign_condition_result = try_to_get_sign_condition(expression_hook, control_graph);
    if (sign_condition_result) {
        str_hook *rest = sign_condition_result->rest;
        const bool boolean_acc = sign_condition_result->value->get.boolean_acc;
        return new aio_result(boolean_acc, rest);
    }
    return aio_assistant::make_function_or_variable(expression_hook, control_graph, cast_to_boolean, make_boolean);
}

static void set_int_value(bool *value, const str_hook *captured_element)
{
    const int int_value = captured_element->to_int();
    if (int_value == 1) {
        *value = true;
    } else if (int_value == 0) {
        *value = false;
    } else {
        throw_error_with_tag(AIO_BOOLEAN_PARSER_INFO_TAG, "Can not cast int to boolean!");
    }
}

static void set_double_value(bool *value, const str_hook *captured_element)
{
    const double double_value = captured_element->to_double();
    if (double_value == 1.0) {
        *value = true;
    } else if (double_value == 0.0) {
        *value = false;
    } else {
        throw_error_with_tag(AIO_BOOLEAN_PARSER_INFO_TAG, "Can not cast double to boolean!");
    }
}

aio_result *aio_expression_parser::aio_boolean_parser::make_boolean(const str_hook *expression_hook)
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
    bool value = false;
    if (is_aio_null_modifier(captured_element)) {
        throw_error_with_str_hook(AIO_BOOLEAN_PARSER_INFO_TAG, "Found null in expression:", expression_hook);
    } else
        //Maybe int value?
    if (captured_element->matches_int()) {
        set_int_value(&value, captured_element);
    } else
        //Maybe double value?
    if (captured_element->matches_double()) {
        set_double_value(&value, captured_element);
    } else
        //Maybe string value?
    if (captured_element->matches_string()) {
        const str_hook *naked_hook = captured_element->lower_quotes();
        if (naked_hook->matches_boolean()) {
            value = naked_hook->to_boolean();
        } else if (naked_hook->matches_int()) {
            set_int_value(&value, naked_hook);
        } else if (naked_hook->matches_double()) {
            set_double_value(&value, naked_hook);
        } else {
            throw_error_with_tag(AIO_BOOLEAN_PARSER_INFO_TAG, "Can not cast string to boolean!");
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
        throw_error_with_tag(AIO_BOOLEAN_PARSER_INFO_TAG, "Can not define type of expression!");
    }
    str_hook *rest_part = new str_hook(expression_str);
    rest_part->start = i;
    rest_part->end = expression_hook->end;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete captured_element;
    //------------------------------------------------------------------------------------------------------------------
    return new aio_result(value, rest_part);
}