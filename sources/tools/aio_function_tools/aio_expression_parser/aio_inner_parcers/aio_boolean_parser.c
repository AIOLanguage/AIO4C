#include <ctype.h>
#include "../../../../../headers/lang/aio_function/aio_result/aio_result.h"
#include "../../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lang/aio_context/aio_context.h"
#include "../../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"

#define AIO_BOOLEAN_PARSER_TAG "AIO_BOOLEAN_PARSER"

/**
 * Declare function.
 */

static aio_result *make_or(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
);

static aio_result *make_boolean(const_str_hook *expression_hook)
{
    const_string expression_str = expression_hook->source_ref;
    int i = expression_hook->start;
    while (!is_sign(expression_str[i]) && i < expression_hook->end) {
        i++;
    }
    str_hook *captured_element = new_str_hook(expression_str);
    captured_element->start = expression_hook->start;
    captured_element->end = i;
    boolean value = 0;
    //Maybe int value?
    if (is_int_hooked(captured_element)) {
        const int int_value = str_hook_to_int(captured_element);
        if (int_value == 1) {
            value = TRUE;
        }
        if (int_value == 0) {
            value = FALSE;
        }
        throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Cannot cast int to boolean!");
    }
    //Maybe double value?
    if (is_double_hooked(captured_element)) {
        const double double_value = str_hook_to_double(captured_element);
        if (double_value == 1.0) {
            value = TRUE;
        }
        if (double_value == 0.0) {
            value = FALSE;
        }
        throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Cannot cast double to boolean!");
    }
    //Maybe string value?
    if (is_string_hooked(captured_element)) {
        const_str_hook *str_hook = lower_str_hook_quotes(captured_element);
        if (is_boolean_hooked(str_hook)) {
            value = str_hook_to_boolean(str_hook);
        } else {
            throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Cannot cast boolean to boolean!");
        }
    }
    //Maybe boolean value?
    if (is_boolean_hooked(captured_element)) {
        value = str_hook_to_boolean(captured_element);
    } else {
        throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Cannot define type of expression!");
    }
    str_hook *rest_part = new_str_hook(expression_str);
    rest_part->start = i;
    rest_part->end = expression_hook->end;
    aio_result *int_result = new_aio_int_result(value, rest_part);
    return int_result;
}

static typedef enum sign {
    SIGN_UNDEFINED, SIGN_EQUALS, SIGN_MORE, SIGN_LESS, SIGN_MORE_OR_EQUALS, SIGN_LESS_OR_EQUALS
} sign;

static aio_result *try_to_get_sign_condition(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    const_string expression_str = expression_hook->source_ref;
    const int start_position = expression_hook->start;
    const int left_border = expression_hook->end;
    int i = start_position;
    point_watcher *sign_watcher = new_point_watcher();
    sign sign = SIGN_UNDEFINED;
    //Found condition:
    while (i < left_border) {
        const char symbol = expression_str[i];
        //Check symbol:
        const_boolean is_equal = is_equal_sign((symbol));
        const_boolean is_more = is_more_sign(symbol);
        const_boolean is_less = is_less_sign(symbol);
        if ((is_equal || is_less || is_more) && sign_watcher->pointer == 0) {
            if (is_equal) {
                sign = SIGN_EQUALS;
            }
            if (is_less) {
                sign = SIGN_LESS;
            }
            if (is_more) {
                sign = SIGN_MORE;
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
    if (sign_watcher->mode != POINT_WATCHER_ACTIVE_MODE) {
        return NULL;
    }
    //Parse left expression:
    const_str_hook *left_expression = new_str_hook_with_start_and_end(expression_str, start_position, i);
    aio_value *left_value = parse_value_hook(left_expression, context, control_graph);
    //Define sign:
    int start_right_expr_pos = i + 1;
    const_boolean is_next_equal_sign = is_equal_sign(expression_str[i + 1]);
    if (sign == SIGN_EQUALS) {
        if (is_next_equal_sign) {
            start_right_expr_pos++;
        } else {
            throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Invalid equal sign in condition");
        }
    }
    if (sign == SIGN_LESS) {
        if (is_next_equal_sign) {
            sign = SIGN_LESS_OR_EQUALS;
            start_right_expr_pos++;
        }
    }
    if (sign == SIGN_MORE) {
        if (is_next_equal_sign) {
            sign = SIGN_MORE_OR_EQUALS;
            start_right_expr_pos++;
        }
    }
    //Find right part:
    int end_right_expr_pos = start_right_expr_pos;
    while (end_right_expr_pos < left_border) {
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
        end_right_expr_pos++;
    }
    const_str_hook *right_expression
            = new_str_hook_with_start_and_end(expression_str, start_right_expr_pos, end_right_expr_pos);
    aio_value *right_value = parse_value_hook(right_expression, context, control_graph);
    //Compare values:
    boolean condition_value = FALSE;
    switch (sign) {
        case SIGN_EQUALS:
            condition_value = are_equal_aio_values(left_value, right_value);
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
            throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Invalid case!");
    }
    //Create next rest:
    str_hook *next_rest = new_str_hook_with_start_and_end(expression_str, end_right_expr_pos, left_border);
    return new_aio_boolean_result(condition_value, next_rest);
}

static aio_result *try_to_get_variable_or_function_condition(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    const_string expression_str = expression_hook->source_ref;
    const int start_position = expression_hook->start;
    int i = start_position;
    const int left_border = expression_hook->end;
    while (i < left_border && (isalpha(expression_str[i]) || (isdigit(expression_str[i]) && i != start_position))) {
        i++;
    }
    const_str_hook *function_or_variable_name = new_str_hook_with_start_and_end(expression_str, start_position, i);
    if (i == left_border) {
        i--;
    }
    if (is_not_empty_hooked_str(function_or_variable_name)) {
        const int function_or_variable_str_length = get_str_hook_size(function_or_variable_name);
        if (i < left_border && is_opening_parenthesis(expression_str[i])) {
            str_hook *in_function_parenthesis = new_str_hook(expression_str);
            in_function_parenthesis->start = start_position + function_or_variable_str_length;
            in_function_parenthesis->end = left_border;
            str_hook_list *expression_hook_list = new_str_hook_list();
            int next_expression_point = 0;
            make_expression_chunks_and_count_next_point(in_function_parenthesis, expression_hook_list,
                                                        &next_expression_point);
            const size_t number_of_chunks = expression_hook_list->size;
            const_str_hook_array expression_hooks = expression_hook_list->hooks;
            aio_value_list *input_values = new_aio_value_list();
            for (int j = 0; j < number_of_chunks; ++j) {
                aio_value *inner_value = parse_value_hook(expression_hooks[j], context, control_graph);
                add_aio_value_in_list(input_values, inner_value);
            }
            aio_bundle *bundle = new_aio_bundle(input_values);
            invoke_static_function_in_context(context, function_or_variable_name, bundle);
            aio_value_list *output_values = bundle->output_values;
            if (output_values->size == 1) {
                aio_value *function_value = cast_to_boolean(output_values->values[0]);
                const int offset = function_or_variable_str_length + next_expression_point;
                str_hook *rest = new_str_hook(expression_str);
                rest->start = start_position + offset;
                rest->end = expression_hook->end;
                return new_aio_result(function_value, rest);
            } else {
                throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Function must return single value!");
            }
        } else {
            const_str_hook *variable_name = function_or_variable_name;
            aio_variable *variable = get_aio_variable_in_function_control_graph(variable_name, control_graph);
            aio_value *value = cast_to_boolean(variable->value);
            str_hook *rest = new_str_hook(expression_str);
            rest->start = start_position + function_or_variable_str_length;
            rest->end = expression_hook->end;
            const_boolean boolean_acc = value->get.boolean_acc;
            return new_aio_int_result(boolean_acc, rest);;
        }
    }
}

static aio_result *make_condition(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    aio_result *sign_condition_result = try_to_get_sign_condition(expression_hook, context, control_graph);
    if (sign_condition_result != NULL) {
        str_hook *rest = sign_condition_result->rest;
        const_boolean boolean_acc = sign_condition_result->value->get.boolean_acc;
        return new_aio_boolean_result(boolean_acc, rest);
    }
    aio_result *variable_or_function_result
            = try_to_get_variable_or_function_condition(expression_hook, context, control_graph);
    if (variable_or_function_result != NULL) {
        str_hook *rest = variable_or_function_result->rest;
        const_boolean boolean_acc = variable_or_function_result->value->get.boolean_acc;
        return new_aio_boolean_result(boolean_acc, rest);
    } else {
        return make_boolean(expression_hook);
    }
}

static aio_result *make_parentheses(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
)
{
    const_string expression_str = expression_hook->source_ref;
    const char first_symbol = expression_str[expression_hook->start];
    if (is_opening_parenthesis(first_symbol)) {
        str_hook *next_hook = new_str_hook(expression_str);
        next_hook->start = expression_hook->start + 1;
        next_hook->end = expression_hook->end;
        aio_result *in_parenthesis_result = make_or(next_hook, context, control_graph);
        const_str_hook *in_parenthesis_hook = in_parenthesis_result->rest;
        const_boolean is_not_empty_rest = is_not_empty_hooked_str(in_parenthesis_hook);
        if (is_not_empty_rest && is_closing_parenthesis(expression_str[in_parenthesis_hook->start])) {
            str_hook *after_parenthesis_hook = new_str_hook(expression_str);
            after_parenthesis_hook->start = in_parenthesis_hook->start + 1;
            after_parenthesis_hook->end = in_parenthesis_hook->end;
            in_parenthesis_result->rest = after_parenthesis_hook;
        } else {
            throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Can not close parenthesis!");
        }
        return in_parenthesis_result;
    }
    return make_condition(expression_hook, context, control_graph);
}

static aio_result *make_and(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
)
{

    aio_result *right_result = make_parentheses(expression_hook, context, control_graph);
    str_hook *right_hook = right_result->rest;
    const_string expression_string = right_hook->source_ref;
    int right_acc = right_result->value->get.int_acc;
    while (TRUE) {
        if (is_empty_hooked_str(right_result->rest)) {
            return right_result;
        }
        const char symbol = expression_string[right_hook->start];
        //Check symbol:
        const_boolean is_multiply = is_multiply_sign(symbol);
        const_boolean is_division = is_division_sign(symbol);
        const_boolean is_mod = is_mod_sign(symbol);
        if (is_multiply || is_division || is_mod) {
            //Create after sign part:
            str_hook *left_hook = new_str_hook(expression_string);
            left_hook->start = right_hook->start + 1;
            left_hook->end = right_hook->end;
            aio_result *left_result = make_parentheses(left_hook, context, control_graph);
            const int left_acc = left_result->value->get.int_acc;
            if (is_multiply) {
                right_acc *= left_acc;
            }
            if (is_division) {
                right_acc /= left_acc;
            }
            if (is_mod) {
                right_acc %= left_acc;
            }
            aio_result *result = new_aio_int_result(right_acc, new_str_hook_by_other(left_result->rest));
            right_result = result;
        } else {
            return right_result;
        }
    }

}

static aio_result *make_or(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
)
{
    aio_result *right_result = make_and(expression_hook, context, control_graph);
    str_hook *right_hook = right_result->rest;
    const_string expression_string = right_hook->source_ref;
    boolean right_acc = right_result->value->get.boolean_acc;
    while (is_not_empty_hooked_str(right_result->rest)) {
        const char symbol = expression_string[right_hook->start];
        if (is_or_sign(symbol)) {
            //Create after sign part:
            str_hook *left_hook = new_str_hook(expression_string);
            left_hook->start = right_hook->start + 1;
            left_hook->end = right_hook->end;
            //Find value after sign part:
            aio_result *left_result = make_and(left_hook, context, control_graph);
            const_boolean left_acc = left_result->value->get.boolean_acc;
            right_acc = right_acc || left_acc;
            right_result = left_result;
        }
    }
    return new_aio_int_result(right_acc, new_str_hook_by_other(right_result->rest));

}

struct aio_value *parse_boolean_value_string(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
)
{
    aio_result *result = make_or(expression_hook, context, control_graph);
    if (is_not_empty_hooked_str(result->rest)) {
        throw_error_with_tag(AIO_BOOLEAN_PARSER_TAG, "Can not fully parse expression!");
    }
    return new_aio_boolean_value(result->value->get.boolean_acc);
}