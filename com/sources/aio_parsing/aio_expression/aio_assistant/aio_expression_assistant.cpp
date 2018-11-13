//runtime:
#include <aio_runtime/aio_ray/aio_ray.h>
#include <aio_runtime/aio_value/aio_value.h>
#include <aio_runtime/aio_result/aio_result.h>
#include <aio_runtime/aio_bundle/aio_bundle.h>
#include <aio_parsing/aio_expression/aio_expression_parser.h>
//lib4aio:
#include <lib4aio_cpp_headers/aio_explorer/aio_explorer.h>
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/struct_list/struct_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook_list/str_hook_list.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>

#define AIO_EXPRESSION_ASSISTANT_ERROR_TAG "AIO_EXPRESSION_ASSISTANT_ERROR"

#define AIO_EXPRESSION_ASSISTANT_DEBUG

#ifdef AIO_EXPRESSION_ASSISTANT_DEBUG

#define AIO_EXPRESSION_ASSISTANT_INFO_TAG "AIO_EXPRESSION_ASSISTANT_INFO"

#endif

aio_result *aio_expression_parser::aio_assistant::make_parentheses(
        const str_hook *expression_hook,
        aio_ray *control_graph,
        aio_value *(*cast_function)(const aio_value *),
        aio_result *(*make_value_function)(const str_hook *)
)
{
    const char *expression_str = expression_hook->get_string();
    const char first_symbol = expression_str[expression_hook->start];
    if (is_opening_parenthesis(first_symbol)) {
        //Prepare to explore parenthesis bounds:
        const unsigned start = expression_hook->start;
        //Create inner expression hook:
        const str_hook *in_parenthesis_hook = aio_explorer::explore_hook_scope(start, '(', ')', expression_hook);
#ifdef AIO_EXPRESSION_ASSISTANT_DEBUG
        log_info_str_hook(AIO_EXPRESSION_ASSISTANT_INFO_TAG, "IN PARENTHESIS HOOK:", in_parenthesis_hook);
#endif
//        in_parenthesis_hook->start = start_parenthesis + 1;
//        in_parenthesis_hook->end = end_parenthesis - 1;
        //Get value into parenthesis:
        aio_value *in_parenthesis_value = aio_expression_parser::parse(in_parenthesis_hook, control_graph);
        //Cast to string:
        aio_value *value = cast_function(in_parenthesis_value);
        //Create next rest:
        str_hook *next_hook = new str_hook(expression_str);
        next_hook->start = in_parenthesis_hook->end;
        next_hook->end = expression_hook->end;
        //Create result:
        aio_result *in_parenthesis_result = new aio_result(value, next_hook);
        return in_parenthesis_result;
    }
    return make_function_or_variable(expression_hook, control_graph, cast_function, make_value_function);
}

/**
 * Not implemented.
 */

aio_result *aio_expression_parser::aio_assistant::make_function_or_variable(
        const str_hook *expression_hook,
        aio_ray *control_graph,
        aio_value *(*cast_function)(const aio_value *),
        aio_result *(*make_value_function)(const str_hook *)
)
{
//    throw_error_with_tag(AIO_EXPRESSION_ASSISTANT_ERROR_TAG, "Functions and variables hasn't implemented in AIO yet!");
//    const char *expression_str = expression_hook->get_string();
//    const unsigned start_position = expression_hook->start;
//    const unsigned right_border = expression_hook->end;
//    unsigned i = start_position;
//    while (i < right_border) {
//        const char symbol = expression_str[i];
//        Check symbol:
//        const bool is_letter = isalpha(symbol);
//        const bool is_digit = isdigit(symbol);
//        if (is_letter || (is_digit && i != start_position)) {
//            i++;
//        } else {
//            break;
//        }
//    }
//    const str_hook *function_or_variable_hook = new str_hook(expression_str, start_position, i);
//    if (i == right_border) {
//        i--;
//    }
//    const bool is_variable_or_function_name = function_or_variable_hook->is_not_empty()
//                                              && aio_ray::is_available_name(function_or_variable_hook);
//    if (is_variable_or_function_name) {
//        const bool is_function_found = is_opening_parenthesis(expression_str[i]);
//        if (is_function_found) {
//            const str_hook *function_name = function_or_variable_hook;
//            Prepare args:
//            str_hook *in_function_parenthesis = new str_hook(expression_str);
//            in_function_parenthesis->start = function_or_variable_hook->end;
//            in_function_parenthesis->end = right_border;
//            Prepare to invoke function:
//            str_hook_list *expression_hook_list = new str_hook_list();
//            unsigned next_expression_point = 0;
//            aio_assistant::make_expression_chunks_and_count_next_point(
//                    in_function_parenthesis,
//                    expression_hook_list,
//                    &next_expression_point
//            );
    //Inflate values from args:
//            struct_list *input_values = new_struct_list(sizeof(aio_value));
//            expression_hook_list->foreach([&control_graph, &input_values](const str_hook *it) {
//                aio_value *inner_value = aio_expression_parser::parse(it, control_graph);
//                add_struct_in_list(input_values, inner_value);
//            });
//
    //Make call:
//            aio_bundle *bundle = new aio_bundle(input_values);
//            aio_struct_list *output_values = invoke_static_function_in_context(
//                    control_graph->context_ref,
//                    function_name,
//                    bundle
//            );
//            if (output_values->size == 1) {
//                aio_value *function_value = cast_function(output_values->values[0]);
//                str_hook *rest = new_str_hook(expression_str);
//                rest->start = next_expression_point;
//                rest->end = expression_hook->end;
//                return new_aio_result(function_value, rest);
//            } else {
//                throw_error_with_tag(AIO_EXPRESSION_ASSISTANT_INFO_TAG, "Function must return single value!");
//            }
//        } else {
//            const str_hook *variable_name = function_or_variable_hook;
//            aio_variable *variable = get_aio_variable_in_function_control_graph(variable_name, control_graph);
//            aio_value *value = cast_function(variable->value);
//            str_hook *rest = new_str_hook_with_start_and_end(expression_str, variable_name->end, expression_hook->end);
//            return new_aio_result(value, rest);;
//        }
//    }
    return make_value_function(expression_hook);
}

void aio_expression_parser::aio_assistant::make_expression_chunks_and_count_next_point(
        const str_hook *expression_hook,
        str_hook_list *expression_list,
        unsigned *next_point
)
{
//    const_string expression_str = expression_hook->source_string;
//    //Skip first opening parenthesis:
//    int parenthesis_up_downer = 1;
//    const int start_position = expression_hook->start + 1;
//    int last_pointer = start_position;
//    for (int j = expression_hook->start + 1; j < expression_hook->end; ++j) {
//        const char symbol = expression_str[j];
//        if (is_opening_parenthesis(symbol)) {
//            parenthesis_up_downer++;
//        }
//        if (is_closing_parenthesis(symbol)) {
//            parenthesis_up_downer--;
//            if (parenthesis_up_downer == 0) {
//                str_hook *inner_expression = new_str_hook(expression_str);
//                inner_expression->start = last_pointer;
//                inner_expression->end = j;
//                add_str_hook_in_list(expression_list, inner_expression);
//                *next_point = j + 1;
//                return;
//            }
//            if (parenthesis_up_downer < 0) {
//                throw_error_with_tag(AIO_EXPRESSION_ASSISTANT_INFO_TAG, "Invalid parenthesis placement!");
//            }
//        }
//        if (is_comma(symbol) && parenthesis_up_downer == 1) {
//            str_hook *inner_expression = new_str_hook(expression_str);
//            inner_expression->start = last_pointer;
//            inner_expression->end = j;
//            add_str_hook_in_list(expression_list, inner_expression);
//            last_pointer = j + 1;
//        }
//    }
    throw_error_with_tag(AIO_EXPRESSION_ASSISTANT_ERROR_TAG, "Incorrect parenthesis placement");
}