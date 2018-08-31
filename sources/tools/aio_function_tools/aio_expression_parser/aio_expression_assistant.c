#include <ctype.h>
#include <lang/aio_function/aio_value/aio_value.h>
#include <lang/aio_function/aio_variable/aio_variable.h>
#include <lang/aio_function/aio_result/aio_result.h>
#include <tools/aio_function_tools/aio_control_graph/aio_function_control_graph_management.h>
#include <lib/utils/string_utils/string_utils.h>
#include <tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <lib/utils/char_utils/char_utils.h>
#include <lib/utils/error_utils/error_utils.h>
#include <lang/aio_reserved_names/aio_reserved_names_container.h>
#include <lang/aio_function/aio_function.h>
#include <tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h>
#include <tools/aio_common_tools/aio_block_body_explorer/aio_block_body_explorer.h>

#define AIO_EXPRESSION_ASSISTANT_TAG "AIO_EXPRESSION_ASSISTANT"

#define AIO_EXPRESSION_ASSISTANT_DEBUG

#ifdef AIO_EXPRESSION_ASSISTANT_DEBUG

#endif

void make_expression_chunks_and_count_next_point(
        const_str_hook *expression_hook,
        str_hook_list *expression_list,
        int *next_point
)
{
    const_string expression_str = expression_hook->source_string;
    //Skip first opening parenthesis:
    int parenthesis_up_downer = 1;
    const int start_position = expression_hook->start + 1;
    int last_pointer = start_position;
    for (int j = expression_hook->start + 1; j < expression_hook->end; ++j) {
        const char symbol = expression_str[j];
        if (is_opening_parenthesis(symbol)) {
            parenthesis_up_downer++;
        }
        if (is_closing_parenthesis(symbol)) {
            parenthesis_up_downer--;
            if (parenthesis_up_downer == 0) {
                str_hook *inner_expression = new_str_hook(expression_str);
                inner_expression->start = last_pointer;
                inner_expression->end = j;
                add_str_hook_in_list(expression_list, inner_expression);
                *next_point = j + 1;
                return;
            }
            if (parenthesis_up_downer < 0) {
                throw_error_with_tag(AIO_EXPRESSION_ASSISTANT_TAG, "Invalid parenthesis placement!");
            }
        }
        if (is_comma(symbol) && parenthesis_up_downer == 1) {
            str_hook *inner_expression = new_str_hook(expression_str);
            inner_expression->start = last_pointer;
            inner_expression->end = j;
            add_str_hook_in_list(expression_list, inner_expression);
            last_pointer = j + 1;
        }
    }
    throw_error_with_tag(AIO_EXPRESSION_ASSISTANT_TAG, "Incorrect parenthesis placement");
}

aio_result *make_function_or_variable(
        const_str_hook *expression_hook,
        const_aio_function_control_graph *control_graph,
        aio_value *(*cast_function)(aio_value *),
        aio_result *(*make_value_function)(const_str_hook *)
)
{
    const_string expression_str = expression_hook->source_string;
    const int start_position = expression_hook->start;
    const int right_border = expression_hook->end;
    int i = start_position;
    while (i < right_border) {
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
    const_str_hook *function_or_variable_hook = new_str_hook_with_start_and_end(expression_str, start_position, i);
    if (i == right_border) {
        i--;
    }
    const_boolean is_variable_or_function_name = is_not_empty_hooked_str(function_or_variable_hook)
                                                 && can_use_name(function_or_variable_hook);
    if (is_variable_or_function_name) {
        const_boolean is_function_found = is_opening_parenthesis(expression_str[i]);
        if (is_function_found) {
            const_str_hook *function_name = function_or_variable_hook;
            str_hook *in_function_parenthesis = new_str_hook(expression_str);
            in_function_parenthesis->start = function_or_variable_hook->end;
            in_function_parenthesis->end = right_border;
            //Prepare to invoke function:
            str_hook_list *expression_hook_list = new_str_hook_list();
            int next_expression_point = 0;
            make_expression_chunks_and_count_next_point(
                    in_function_parenthesis,
                    expression_hook_list,
                    &next_expression_point
            );
            const size_t number_of_chunks = expression_hook_list->size;
            const_str_hook_array expression_hooks = expression_hook_list->hooks;
            aio_value_list *input_values = new_aio_value_list();
            for (int j = 0; j < number_of_chunks; ++j) {
                aio_value *inner_value = parse_value_hook(expression_hooks[j], control_graph);
                add_aio_value_in_list(input_values, inner_value);
            }
            aio_bundle *bundle = new_aio_bundle(input_values);
            aio_value_list *output_values = invoke_static_function_in_context(
                    control_graph->context_ref,
                    function_name,
                    bundle
            );
            if (output_values->size == 1) {
                aio_value *function_value = cast_function(output_values->values[0]);
                str_hook *rest = new_str_hook(expression_str);
                rest->start = next_expression_point;
                rest->end = expression_hook->end;
                return new_aio_result(function_value, rest);
            } else {
                throw_error_with_tag(AIO_EXPRESSION_ASSISTANT_TAG, "Function must return single value!");
            }
        } else {
            const_str_hook *variable_name = function_or_variable_hook;
            aio_filed *variable = get_aio_variable_in_function_control_graph(variable_name, control_graph);
            aio_value *value = cast_function(variable->value);
            str_hook *rest = new_str_hook_with_start_and_end(expression_str, variable_name->end, expression_hook->end);
            return new_aio_result(value, rest);;
        }
    }
    return make_value_function(expression_hook);
}

aio_result *make_parentheses(
        const_str_hook *expression_hook,
        const_aio_function_control_graph *control_graph,
        aio_value *(*cast_function)(aio_value *),
        aio_result *(*make_value_function)(const_str_hook *)
)
{
    const_string expression_str = expression_hook->source_string;
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
        //Get value into parenthesis:
        aio_value *in_parenthesis_value = parse_value_hook(in_parenthesis_hook, control_graph);
        //Cast to string:
        aio_value *value = cast_function(in_parenthesis_value);
        //Create next rest:
        str_hook *next_hook = new_str_hook(expression_str);
        next_hook->start = end_parenthesis;
        next_hook->end = expression_hook->end;
        //Create result:
        aio_result *in_parenthesis_result = new_aio_result(value, next_hook);
        return in_parenthesis_result;
    }
    return make_function_or_variable(expression_hook, control_graph, cast_function, make_value_function);
}