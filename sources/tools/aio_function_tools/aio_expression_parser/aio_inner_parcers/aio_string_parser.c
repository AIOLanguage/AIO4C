#include <ctype.h>
#include "../../../../../headers/lib/utils/str_hook/str_hook.h"
#include "../../../../../headers/lang/aio_context/aio_context.h"
#include "../../../../../headers/lang/aio_function/aio_result/aio_result.h"
#include "../../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lib/utils/string_utils/string_builder.h"
#include "../../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"

#define AIO_STRING_PARSER_DEBUG

#ifdef AIO_STRING_PARSER_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"
#include "../../../../../headers/tools/aio_common_tools/aio_block_body_explorer/aio_block_body_explorer.h"

#endif

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
#ifdef AIO_STRING_PARSER_DEBUG
    log_info_str_hook(AIO_STRING_PARSER_TAG, "Make string with expression:", expression_hook);
#endif
    const_string expression_str = expression_hook->source_ref;
    int i = expression_hook->start;
    while (!is_tilde_sign(expression_str[i]) && i < expression_hook->end) {
        i++;
    }
    str_hook *captured_element = new_str_hook(expression_str);
    captured_element->start = expression_hook->start;
    captured_element->end = i;
    const_str_hook *clean_string_value = NULL;
    if (is_string_hooked(captured_element)) {
        clean_string_value = lower_str_hook_quotes(captured_element);
    } else {
        clean_string_value = captured_element;
    }
    string value = substring_by_str_hook(clean_string_value);
    str_hook *rest_part = new_str_hook(expression_str);
    rest_part->start = i;
    rest_part->end = expression_hook->end;
#ifdef AIO_STRING_PARSER_DEBUG
    log_info_string(AIO_STRING_PARSER_TAG, "Made string:", value);
    log_info_str_hook(AIO_STRING_PARSER_TAG, "Rest:", rest_part);
#endif
    return new_aio_string_result(value, rest_part);
}

static aio_result *make_function_or_variable(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
#ifdef AIO_STRING_PARSER_DEBUG
    log_info_str_hook(AIO_STRING_PARSER_TAG, "Make function or variable with expression:", expression_hook);
#endif
    const_string expression_str = expression_hook->source_ref;
    const int start_position = expression_hook->start;
    const int left_border = expression_hook->end;
    int i = start_position;
    while (i < left_border) {
        const char symbol = expression_str[i];
        //Check symbol:
        const_boolean is_letter = isalpha(symbol);
        const_boolean is_digit = isdigit(symbol);
        if (is_letter || (is_digit && i != start_position)) {
            i++;
        } else {
            break;
        }
    }
    const_str_hook *function_or_variable_name = new_str_hook_with_start_and_end(expression_str, start_position, i);
#ifdef AIO_STRING_PARSER_DEBUG
    log_info_str_hook(AIO_STRING_PARSER_TAG, "Captured element:", function_or_variable_name);
#endif
    if (i == left_border) {
        i--;
    }
    if (is_not_empty_hooked_str(function_or_variable_name)) {
        if (i < left_border && is_opening_parenthesis(expression_str[i])) {
            const_str_hook *function_name = function_or_variable_name;
#ifdef AIO_STRING_PARSER_DEBUG
            log_info_str_hook(AIO_STRING_PARSER_TAG, "This is function:", function_name);
#endif
            str_hook *in_function_parenthesis = new_str_hook(expression_str);
            in_function_parenthesis->start = function_or_variable_name->end;
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
#ifdef AIO_STRING_PARSER_DEBUG
            log_info_str_hook(AIO_STRING_PARSER_TAG, "Is variable:", variable_name);
#endif
            aio_variable *variable = get_aio_variable_in_function_control_graph(variable_name, control_graph);
            aio_value *value = cast_to_string(variable->value);
            str_hook *rest = new_str_hook(expression_str);
            rest->start = variable_name->end;
            rest->end = expression_hook->end;
            string string_acc = value->get.string_acc;
            return new_aio_string_result(string_acc, rest);;
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
#ifdef AIO_STRING_PARSER_DEBUG
    log_info_str_hook(AIO_STRING_PARSER_TAG, "Make parenthesis with expression:", expression_hook);
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
#ifdef AIO_STRING_PARSER_DEBUG
        log_info_str_hook(AIO_STRING_PARSER_TAG, "In parenthesis expression hook:", in_parenthesis_hook);
#endif
        //Get value into parenthesis:
        aio_value *in_parenthesis_value = parse_value_hook(in_parenthesis_hook, context, control_graph);
        //Cast to string:
        aio_value *string_value = cast_to_string(in_parenthesis_value);
        string str = new_string(string_value->get.string_acc);
        //Create next rest:
        str_hook *next_hook = new_str_hook(expression_str);
        next_hook->start = end_parenthesis + 1;
        next_hook->end = expression_hook->end;
        //Create result:
        aio_result *in_parenthesis_result = new_aio_string_result(str, next_hook);
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
#ifdef AIO_STRING_PARSER_DEBUG
    log_info_str_hook(AIO_STRING_PARSER_TAG, "Make plus with expression:", expression_hook);
#endif
    aio_result *right_result = make_parentheses(expression_hook, context, control_graph);
    const_string expression_string = right_result->rest->source_ref;
    const_string right_acc = right_result->value->get.string_acc;
#ifdef AIO_STRING_PARSER_DEBUG
    log_info_str_hook(AIO_STRING_PARSER_TAG, "After plus rest:", right_result->rest);
#endif
    //Create string builder:
    string_builder *str_builder = new_string_builder();
    append_string(str_builder, right_acc);
    while (is_not_empty_hooked_str(right_result->rest)) {
        const char symbol = expression_string[right_result->rest->start];
        //Check symbol:
        if (is_tilde_sign(symbol)) {
            //Create after sign part:
            str_hook *next_hook = new_str_hook(expression_string);
            next_hook->start = right_result->rest->start + 1;
            next_hook->end = right_result->rest->end;
            //Find value after sign part:
            aio_result *left_result = make_parentheses(next_hook, context, control_graph);
            const_string left_acc = left_result->value->get.string_acc;
#ifdef AIO_STRING_PARSER_DEBUG
            log_info_str_hook(AIO_STRING_PARSER_TAG, "AFTER LEFT REST:", left_result->rest);
#endif
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
#ifdef AIO_STRING_PARSER_DEBUG
    log_info(AIO_STRING_PARSER_TAG, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    log_info_str_hook(AIO_STRING_PARSER_TAG, "Start to parse string expression:", expression_hook);
#endif
    aio_result *result = make_plus(expression_hook, context, control_graph);
    if (is_not_empty_hooked_str(result->rest)) {
        throw_error_with_tag(AIO_STRING_PARSER_TAG, "Can not fully parse expression!");
    }
#ifdef AIO_STRING_PARSER_DEBUG
    log_info_string(AIO_STRING_PARSER_TAG, "String parsing complete", result->value->get.string_acc);
#endif
    aio_value *string_value = new_aio_string_value(result->value->get.string_acc);
    return string_value;
}