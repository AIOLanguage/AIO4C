
#include "../../../../../headers/lang/aio_function/aio_result/aio_result.h"
#include "../../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lang/aio_context/aio_context.h"
#include "../../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"
#include "../../../../../headers/tools/aio_common_tools/aio_block_body_explorer/aio_block_body_explorer.h"

#define AIO_BOOLEAN_PARSER_TAG "AIO_BOOLEAN_PARSER"

#define AIO_BOOLEAN_PARSER_DEBUG

#ifdef AIO_BOOLEAN_PARSER_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

static void set_int_value(boolean *value, const_str_hook *captured_element)
{
    const int int_value = str_hook_to_int(captured_element);
    if (int_value == 1) {
        *value = TRUE;
    } else if (int_value == 0) {
        *value = FALSE;
    } else {
        throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Can not cast int to boolean!");
    }
}

static void set_double_value(boolean *value, const_str_hook *captured_element)
{
    const double double_value = str_hook_to_double(captured_element);
    if (double_value == 1.0) {
        *value = TRUE;
    } else if (double_value == 0.0) {
        *value = FALSE;
    } else {
        throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Can not cast double to boolean!");
    }
}

static aio_result *make_boolean(const_str_hook *expression_hook)
{
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "Make boolean for expression hook:", expression_hook);
#endif
    const_string expression_str = expression_hook->source_ref;
    const int right_border = expression_hook->end;
    int i = expression_hook->start;
    while (!is_sign(expression_str[i]) && i < right_border) {
        i++;
    }
    str_hook *captured_element = new_str_hook(expression_str);
    captured_element->start = expression_hook->start;
    captured_element->end = i;
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "Captured element:", captured_element);
#endif
    boolean value = 0;
    //Maybe int value?
    if (is_int_hooked(captured_element)) {
        set_int_value(&value, captured_element);
    } else
        //Maybe double value?
    if (is_double_hooked(captured_element)) {
        set_double_value(&value, captured_element);
    } else
        //Maybe string value?
    if (is_string_hooked(captured_element)) {
        const_str_hook *naked_hook = lower_str_hook_quotes(captured_element);
        if (is_boolean_hooked(naked_hook)) {
            value = str_hook_to_boolean(naked_hook);
        } else if (is_int_hooked(naked_hook)) {
            set_int_value(&value, naked_hook);
        } else if (is_double_hooked(naked_hook)) {
            set_double_value(&value, naked_hook);
        } else {
            throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Can not cast string to boolean!");
        }
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_const_str_hook(naked_hook);
    } else
        //Maybe boolean value?
    if (is_boolean_hooked(captured_element)) {
        value = str_hook_to_boolean(captured_element);
    } else {
        throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Can not define type of expression!");
    }
    str_hook *rest_part = new_str_hook(expression_str);
    rest_part->start = i;
    rest_part->end = expression_hook->end;
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "After boolean making rest:", rest_part);
#endif
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_str_hook(captured_element);
    return new_aio_int_result(value, rest_part);
}

static enum sign {
    SIGN_UNDEFINED, SIGN_EQUALS, SIGN_NOT_EQUALS, SIGN_MORE, SIGN_LESS, SIGN_MORE_OR_EQUALS, SIGN_LESS_OR_EQUALS
};

static aio_result *try_to_get_sign_condition(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "Try to get sign condition for expression hook:", expression_hook);
#endif
    const_string expression_str = expression_hook->source_ref;
    const int start_position = expression_hook->start;
    const int right_border = expression_hook->end;
    int i = start_position;
    point_watcher *sign_watcher = new_point_watcher();
    enum sign sign_type = SIGN_UNDEFINED;
    //Find left part of sign condition:
    while (i < right_border) {
        const char symbol = expression_str[i];
        //Check symbol:
        const_boolean is_equal = is_equal_sign((symbol));
        const_boolean is_more = is_more_sign(symbol);
        const_boolean is_less = is_less_sign(symbol);
        const_boolean is_not_equal = is_exclamation_point(symbol);
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
            sign_watcher->mode = POINT_WATCHER_ACTIVE_MODE;
            break;
        }
        if (is_opening_parenthesis(symbol)) {
            sign_watcher->pointer++;
        }
        if (is_closing_parenthesis(symbol)) {
            sign_watcher->pointer--;
            if (sign_watcher->pointer < 0) {
                throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Invalid parenthesis placement!");
            }
        }
        i++;
    }
    //If not found:
    if (sign_watcher->mode != POINT_WATCHER_ACTIVE_MODE) {
        return NULL;
    }
    //Parse left expression:
    const_str_hook *left_expression = new_str_hook_with_start_and_end(expression_str, start_position, i);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "Captured left expression of condition:", left_expression);
#endif
    aio_value *left_value = parse_value_hook(left_expression, context, control_graph);
    //Uniquely define sign & start right expression position:
    int start_right_expr_pos = i + 1;
    const_boolean is_next_equal_sign = is_equal_sign(expression_str[i + 1]);
    if (sign_type == SIGN_EQUALS) {
        if (is_next_equal_sign) {
            start_right_expr_pos++;
        } else {
            throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Invalid equal sign in condition");
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
            throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Invalid equal sign in condition");
        }
    }
    //Find right part:
    int end_right_expr_pos = start_right_expr_pos;
    while (end_right_expr_pos < right_border) {
        const char symbol = expression_str[end_right_expr_pos];
        //Check symbol:
        const_boolean is_and = is_and_sign(symbol);
        const_boolean is_or = is_or_sign(symbol);
        if ((is_and || is_or) && sign_watcher->pointer == 0) {
            break;
        }
        if (is_opening_parenthesis(symbol)) {
            sign_watcher->pointer++;
        }
        if (is_closing_parenthesis(symbol)) {
            sign_watcher->pointer--;
            if (sign_watcher->pointer < 0) {
                throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Invalid parenthesis placement!");
            }
        }
        //Shift right end border for right expression:
        end_right_expr_pos++;
    }
    const_str_hook *right_expression
            = new_str_hook_with_start_and_end(expression_str, start_right_expr_pos, end_right_expr_pos);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "Captured right expression of condition:", right_expression);
#endif
    aio_value *right_value = parse_value_hook(right_expression, context, control_graph);
    //Compare values:
    boolean condition_value = FALSE;
    switch (sign_type) {
        case SIGN_EQUALS:
            condition_value = are_equal_aio_values(left_value, right_value);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
            log_info_boolean(AIO_BOOLEAN_PARSER_TAG, "Are equals:", condition_value);
#endif
            break;
        case SIGN_NOT_EQUALS:
            condition_value = are_not_equal_aio_values(left_value, right_value);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
            log_info_boolean(AIO_BOOLEAN_PARSER_TAG, "Are not equals:", condition_value);
#endif
            break;
        case SIGN_MORE:
            condition_value = is_more_aio_value_then_other(left_value, right_value);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
            log_info_boolean(AIO_BOOLEAN_PARSER_TAG, "Left more than right:", condition_value);
#endif
            break;
        case SIGN_LESS:
            condition_value = is_less_aio_value_then_other(left_value, right_value);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
            log_info_boolean(AIO_BOOLEAN_PARSER_TAG, "Left less than right:", condition_value);
#endif
            break;
        case SIGN_MORE_OR_EQUALS:
            condition_value = is_more_or_equals_aio_value_then_other(left_value, right_value);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
            log_info_boolean(AIO_BOOLEAN_PARSER_TAG, "Left more or equals than right:", condition_value);
#endif
            break;
        case SIGN_LESS_OR_EQUALS:
            condition_value = is_less_or_equals_aio_value_then_other(left_value, right_value);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
            log_info_boolean(AIO_BOOLEAN_PARSER_TAG, "Left less or equals than right:", condition_value);
#endif
            break;
        case SIGN_UNDEFINED:
            throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Invalid case!");
    }
    //Create next rest:
    str_hook *next_rest = new_str_hook_with_start_and_end(expression_str, end_right_expr_pos, right_border);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "Next rest after condition:", next_rest);
#endif
    return new_aio_boolean_result(condition_value, next_rest);
}

static aio_result *make_condition(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "Make boolean condition for expression hook:", expression_hook);
#endif
    aio_result *sign_condition_result = try_to_get_sign_condition(expression_hook, context, control_graph);
    if (sign_condition_result != NULL) {
        str_hook *rest = sign_condition_result->rest;
        const_boolean boolean_acc = sign_condition_result->value->get.boolean_acc;
        return new_aio_boolean_result(boolean_acc, rest);
    }
    return make_function_or_variable(expression_hook, context, control_graph, cast_to_boolean, make_boolean);
}

static aio_result *make_boolean_parentheses(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "Make parenthesis for:", expression_hook);
#endif
    const_string expression_str = expression_hook->source_ref;
    const char first_symbol = expression_str[expression_hook->start];
    if (is_opening_parenthesis(first_symbol)) {
        //Prepare to explore parenthesis bounds:
        int start_parenthesis = expression_hook->start;
        int end_parenthesis = 0;
        explore_aio_header_bounds(expression_str, &start_parenthesis, &end_parenthesis);
        //Create inner expression hook:
        str_hook *in_parenthesis_hook = new_str_hook(expression_str);
        in_parenthesis_hook->start = start_parenthesis + 1;
        in_parenthesis_hook->end = end_parenthesis - 1;
#ifdef AIO_BOOLEAN_PARSER_DEBUG
        log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "In parenthesis expression hook:", in_parenthesis_hook);
#endif
        //Get value into parenthesis:
        aio_value *in_parenthesis_value = parse_value_hook(in_parenthesis_hook, context, control_graph);
        //Cast to string:
        aio_value *value = cast_to_boolean(in_parenthesis_value);
        //Create next rest:
        str_hook *next_hook = new_str_hook(expression_str);
        next_hook->start = end_parenthesis;
        next_hook->end = expression_hook->end;
        //Create result:
        aio_result *in_parenthesis_result = new_aio_result(value, next_hook);
        return in_parenthesis_result;
    }
    return make_condition(expression_hook, context, control_graph);
}

static aio_result *make_and(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "Make and for expression:", expression_hook);
#endif
    const_string expression_string = expression_hook->source_ref;
    aio_result *left_result = make_boolean_parentheses(expression_hook, context, control_graph);
    str_hook *left_hook = new_str_hook_by_other(left_result->rest);
    boolean left_acc = left_result->value->get.boolean_acc;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_aio_result(left_result);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "After left parenthesis rest:", left_hook);
#endif
    while (is_not_empty_hooked_str(left_hook)) {
        const char symbol = expression_string[left_hook->start];
        if (is_and_sign(symbol)) {
            //Create after sign part:
            str_hook *next_hook = new_str_hook(expression_string);
            next_hook->start = left_hook->start + 1;
            next_hook->end = left_hook->end;
            aio_result *right_result = make_boolean_parentheses(next_hook, context, control_graph);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
            log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "After right parenthesis:", right_result->rest);
#endif
            const_boolean right_acc = right_result->value->get.boolean_acc;
            left_acc = left_acc && right_acc;
#ifdef AIO_BOOLEAN_PARSER_DEBUG
            log_info_boolean(AIO_BOOLEAN_PARSER_TAG, "After and acc:", left_acc);
#endif
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
    return new_aio_boolean_result(left_acc, rest);
}

static aio_result *make_or(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "Make or for expression:", expression_hook);
#endif
    const_string expression_string = expression_hook->source_ref;
    aio_result *left_result = make_and(expression_hook, context, control_graph);
    str_hook *left_hook = new_str_hook_by_other(left_result->rest);
    boolean left_acc = left_result->value->get.boolean_acc;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_aio_result(left_result);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "After left and rest:", left_hook);
#endif
    while (is_not_empty_hooked_str(left_hook)) {
        const char symbol = expression_string[left_hook->start];
        if (is_or_sign(symbol)) {
            //Create after sign part:
            str_hook *next_hook = new_str_hook(expression_string);
            next_hook->start = left_hook->start + 1;
            next_hook->end = left_hook->end;
            //Find value after sign part:
            aio_result *right_result = make_and(next_hook, context, control_graph);
#ifdef AIO_BOOLEAN_PARSER_DEBUG
            log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "After right and rest", right_result->rest);
#endif
            const_boolean right_acc = right_result->value->get.boolean_acc;
            left_acc = left_acc || right_acc;
#ifdef AIO_BOOLEAN_PARSER_DEBUG
            log_info_boolean(AIO_BOOLEAN_PARSER_TAG, "After or acc:", left_acc);
#endif
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
    return new_aio_boolean_result(left_acc, rest);
}

aio_value *parse_boolean_value_string(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info(AIO_BOOLEAN_PARSER_TAG, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    log_info_str_hook(AIO_BOOLEAN_PARSER_TAG, "Start parse boolean expression:", expression_hook);
#endif
    aio_result *result = make_or(expression_hook, context, control_graph);
    if (is_not_empty_hooked_str(result->rest)) {
        throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Can not fully parse expression!");
    }
    const_boolean result_boolean_acc = result->value->get.boolean_acc;
#ifdef AIO_BOOLEAN_PARSER_DEBUG
    log_info_boolean(AIO_BOOLEAN_PARSER_TAG, "Boolean parser is complete!", result_boolean_acc);
#endif
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_aio_result(result);
    return new_aio_boolean_value(result_boolean_acc);
}