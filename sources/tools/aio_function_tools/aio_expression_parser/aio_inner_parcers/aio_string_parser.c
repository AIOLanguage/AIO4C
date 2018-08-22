#include <ctype.h>
#include "../../../../../headers/lib/utils/str_hook/str_hook.h"
#include "../../../../../headers/lang/aio_context/aio_context.h"
#include "../../../../../headers/lang/aio_function/aio_result/aio_result.h"
#include "../../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lang/aio_function/aio_value/aio_value.h"
#include "../../../../../headers/lib/utils/string_utils/string_builder.h"
#include "../../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"

#define AIO_STRING_PARSER_TAG "AIO_STRING_PARSER"

/**
 * Declare function.
 */

static aio_result *make_plus(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
);

/**
 * Business logic.
 */

static aio_result *make_string(const_str_hook *expression_hook)
{
    const_string expression_str = expression_hook->source_ref;
    int i = expression_hook->start;
    while (!is_sign(expression_str[i]) && i < expression_hook->end) {
        i++;
    }
    str_hook *captured_element = new_str_hook(expression_str);
    captured_element->start = expression_hook->start;
    captured_element->end = i;
    string value = substring_by_str_hook(captured_element);
    str_hook *rest_part = new_str_hook(expression_str);
    rest_part->start = i;
    rest_part->end = expression_hook->end;
    return new_aio_string_result(value, rest_part);
}

static aio_result *make_function_or_variable(
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
        const int function_or_variable_offset = get_str_hook_size(function_or_variable_name);
        if (i < left_border && is_opening_parenthesis(expression_str[i])) {
            str_hook *in_function_parenthesis = new_str_hook(expression_str);
            in_function_parenthesis->start = start_position + function_or_variable_offset;
            in_function_parenthesis->end = left_border;
            //Prepare to invoke function:
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
                aio_value *function_value = cast_to_string(output_values->values[0]);
                str_hook *rest = new_str_hook(expression_str);
                rest->start = next_expression_point;
                rest->end = expression_hook->end;
                return new_aio_result(function_value, rest);
            } else {
                throw_error_with_tag(AIO_STRING_PARSER_TAG, "Function must return single value!");
            }
        } else {
            const_str_hook *variable_name = function_or_variable_name;
            aio_variable *variable = get_aio_variable_in_function_control_graph(variable_name, control_graph);
            aio_value *value = cast_to_string(variable->value);
            str_hook *rest = new_str_hook(expression_str);
            rest->start = start_position + function_or_variable_offset;
            rest->end = expression_hook->end;
            const double double_acc = value->get.double_acc;
            return new_aio_double_result(double_acc, rest);;
        }
    }
    return make_string(expression_hook);
}

static aio_result *make_parentheses(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    const_string expression_str = expression_hook->source_ref;
    const char first_symbol = expression_str[expression_hook->start];
    if (is_opening_parenthesis(first_symbol)) {
        str_hook *next_hook = new_str_hook(expression_str);
        next_hook->start = expression_hook->start + 1;
        next_hook->end = expression_hook->end;
        aio_result *in_parenthesis_result = make_plus(next_hook, context, control_graph);
        const_str_hook *in_parenthesis_hook = in_parenthesis_result->rest;
        const_boolean is_not_empty_rest = is_not_empty_hooked_str(in_parenthesis_hook);
        const_boolean is_closing_parenthesis_cond = is_closing_parenthesis(expression_str[in_parenthesis_hook->start]);
        if (is_not_empty_rest && is_closing_parenthesis_cond) {
            str_hook *after_parenthesis_hook = new_str_hook(expression_str);
            after_parenthesis_hook->start = in_parenthesis_hook->start + 1;
            after_parenthesis_hook->end = in_parenthesis_hook->end;
            in_parenthesis_result->rest = after_parenthesis_hook;
        } else {
            throw_error_with_tag(AIO_STRING_PARSER_TAG, "Can not close parenthesis!");
        }
        return in_parenthesis_result;
    }
    return make_function_or_variable(expression_hook, context, control_graph);
}

static aio_result *make_plus(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    aio_result *right_result = make_parentheses(expression_hook, context, control_graph);
    str_hook *right_hook = right_result->rest;
    const_string expression_string = right_hook->source_ref;
    const_string right_acc = right_result->value->get.string_acc;
    string_builder *str_builder = new_string_builder();
    append_string(str_builder, right_acc);
    while (is_not_empty_hooked_str(right_result->rest)) {
        const char symbol = expression_string[right_hook->start];
        //Check symbol:
        if (is_tilde_sign(symbol)) {
            //Create after sign part:
            str_hook *left_hook = new_str_hook(expression_string);
            left_hook->start = right_hook->start + 1;
            left_hook->end = right_hook->end;
            //Find value after sign part:
            aio_result *left_result = make_parentheses(left_hook, context, control_graph);
            const_string left_acc = left_result->value->get.string_acc;
            append_string(str_builder, left_acc);
            right_result = left_result;
        }
    }
    string new_string = pop_string_from_builder(str_builder);
    return new_aio_string_result(new_string, new_str_hook_by_other(right_result->rest));
}


struct aio_value *parse_string_value_string(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    aio_result *result = make_plus(expression_hook, context, control_graph);
    if (is_not_empty_hooked_str(result->rest)) {
        throw_error_with_tag(AIO_STRING_PARSER_TAG, "Can not fully parse expression!");
    }
    aio_value *double_value = new_aio_double_value(result->value->get.double_acc);
    return double_value;
}