#include <ctype.h>
#include "../../../../headers/lib/utils/str_hook/str_hook.h"
#include "../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lang/aio_context/aio_context.h"
#include "../../../../headers/lang/aio_function/aio_result/aio_result.h"
#include "../../../../headers/tools/aio_common_tools/aio_block_body_explorer/aio_block_body_explorer.h"
#include "../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"
#include "../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"

#define AIO_EXPRESSION_ASSISTANT_TAG "AIO_EXPRESSION_ASSISTANT"

#define AIO_EXPRESSION_ASSISTANT_DEBUG

#ifdef AIO_EXPRESSION_ASSISTANT_DEBUG

#include "../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

void make_expression_chunks_and_count_next_point(
        const_str_hook *expression_hook,
        str_hook_list *expression_list,
        int *next_point
)
{
    const_string expression_str = expression_hook->source_ref;
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
            if (parenthesis_up_downer < 0) {
                throw_error_with_tag(AIO_EXPRESSION_ASSISTANT_TAG, "Invalid parenthesis placement!");
            }
            if (parenthesis_up_downer == 0) {
                str_hook *inner_expression = new_str_hook(expression_str);
                inner_expression->start = last_pointer,
                        inner_expression->end = j;
                add_str_hook_in_list(expression_list, inner_expression);
                *next_point = j + 1;
                return;
            }
        }
        if (is_comma(symbol) && parenthesis_up_downer == 1) {
            str_hook *inner_expression = new_str_hook(expression_str);
            inner_expression->start = last_pointer,
                    inner_expression->end = j;
            add_str_hook_in_list(expression_list, inner_expression);
            last_pointer = j + 1;
        }
    }
    throw_error_with_tag(AIO_EXPRESSION_ASSISTANT_TAG, "Incorrect parenthesis placement");
}

struct aio_result *make_function_or_variable(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph,
        struct aio_value *(*cast_function)(struct aio_value *),
        struct aio_result *(*make_value_function)(const struct str_hook *)
)
{
#ifdef AIO_EXPRESSION_ASSISTANT_DEBUG
    log_info_str_hook(AIO_EXPRESSION_ASSISTANT_TAG, "Make function or variable with expression:", expression_hook);
#endif
    const_string expression_str = expression_hook->source_ref;
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
    const_str_hook *function_or_variable_name = new_str_hook_with_start_and_end(expression_str, start_position, i);
#ifdef AIO_EXPRESSION_ASSISTANT_DEBUG
    log_info_str_hook(AIO_EXPRESSION_ASSISTANT_TAG, "Captured element:", function_or_variable_name);
#endif
    if (i == right_border) {
        i--;
    }
    if (is_not_empty_hooked_str(function_or_variable_name)) {
        if (i < right_border && is_opening_parenthesis(expression_str[i])) {
            const_str_hook *function_name = function_or_variable_name;
#ifdef AIO_EXPRESSION_ASSISTANT_DEBUG
            log_info_str_hook(AIO_EXPRESSION_ASSISTANT_TAG, "This is function:", function_name);
#endif
            str_hook *in_function_parenthesis = new_str_hook(expression_str);
            in_function_parenthesis->start = function_or_variable_name->end;
            in_function_parenthesis->end = right_border;
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
                aio_value *function_value = cast_function(output_values->values[0]);
                str_hook *rest = new_str_hook(expression_str);
                rest->start = next_expression_point;
                rest->end = expression_hook->end;
                return new_aio_result(function_value, rest);
            } else {
                throw_error_with_tag(AIO_EXPRESSION_ASSISTANT_TAG, "Function must return single value!");
            }
        } else {
            const_str_hook *variable_name = function_or_variable_name;
#ifdef AIO_EXPRESSION_ASSISTANT_DEBUG
            log_info_str_hook(AIO_EXPRESSION_ASSISTANT_TAG, "Is variable:", variable_name);
#endif
            aio_variable *variable = get_aio_variable_in_function_control_graph(variable_name, control_graph);
            aio_value *value = cast_function(variable->value);
            str_hook *rest = new_str_hook(expression_str);
            rest->start = variable_name->end;
            rest->end = expression_hook->end;
            return new_aio_result(value, rest);;
        }
    }
    return make_value_function(expression_hook);
}

struct aio_result *make_parentheses(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph,
        struct aio_value *(*cast_function)(struct aio_value *),
        struct aio_result *(*make_value_function)(const struct str_hook *)
)
{
#ifdef AIO_EXPRESSION_ASSISTANT_DEBUG
    log_info(AIO_EXPRESSION_ASSISTANT_TAG, "Make parenthesis...");
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
#ifdef AIO_EXPRESSION_ASSISTANT_TAG
        log_info_str_hook(AIO_EXPRESSION_ASSISTANT_TAG, "In parenthesis expression hook:", in_parenthesis_hook);
#endif
        //Get value into parenthesis:
        aio_value *in_parenthesis_value = parse_value_hook(in_parenthesis_hook, context, control_graph);
#ifdef AIO_EXPRESSION_ASSISTANT_DEBUG
        log_info_aio_value(AIO_EXPRESSION_ASSISTANT_TAG, "In parenthesis value:", in_parenthesis_value);
#endif
        //Cast to string:
        aio_value *value = cast_function(in_parenthesis_value);
#ifdef AIO_EXPRESSION_ASSISTANT_DEBUG
        log_info_aio_value(AIO_EXPRESSION_ASSISTANT_TAG, "In parenthesis cast value:", value);
#endif
        //Create next rest:
        str_hook *next_hook = new_str_hook(expression_str);
        next_hook->start = end_parenthesis;
        next_hook->end = expression_hook->end;
        //Create result:
#ifdef AIO_EXPRESSION_ASSISTANT_DEBUG
        log_info_str_hook(AIO_EXPRESSION_ASSISTANT_TAG, "After parenthesis rest:", next_hook);
#endif
        aio_result *in_parenthesis_result = new_aio_result(value, next_hook);
        return in_parenthesis_result;
    }
    return make_function_or_variable(expression_hook, context, control_graph, cast_function, make_value_function);
}