#include <mem.h>
#include <lang/aio_function/aio_result/aio_result.h>
#include <lib/utils/str_hook/str_hook.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <lib/utils/string_utils/string_utils.h>
#include <lib/utils/char_utils/char_utils.h>
#include <lib/utils/error_utils/error_utils.h>
#include <tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h>
#include <tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h>
#include <lang/aio_function/aio_value/aio_value.h>
#include <lib/utils/string_utils/string_builder.h>

#define AIO_STRING_PARSER_DEBUG

#ifdef AIO_STRING_PARSER_DEBUG

#endif

#define AIO_STRING_PARSER_TAG "AIO_STRING_PARSER"

static aio_result *make_string(const_str_hook *expression_hook)
{
    const_string expression_str = expression_hook->source_string;
    int i = expression_hook->start;
    while (!is_tilde_sign(expression_str[i]) && i < expression_hook->end) {
        i++;
    }
    str_hook *captured_element = new_str_hook(expression_str);
    captured_element->start = expression_hook->start;
    captured_element->end = i;
    str_hook *clean_string_value = NULL;
    if (is_null_hooked(captured_element)) {
        throw_error_with_hook(AIO_STRING_PARSER_TAG, "Found null in expression:", expression_hook);
    } else if (is_int_hooked(captured_element) || is_double_hooked(captured_element) ||
               is_boolean_hooked(captured_element)) {
        clean_string_value = new_str_hook_by_other(captured_element);
    } else if (is_string_hooked(captured_element)) {
        const_str_hook *naked_hook = lower_str_hook_quotes(captured_element);
        clean_string_value = new_str_hook_by_other(naked_hook);
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_const_str_hook(naked_hook);
    } else {
        throw_error_with_tag(AIO_STRING_PARSER_TAG, "Cannot define type of expression!");
    }
    string value = substring_by_str_hook(clean_string_value);
    str_hook *rest_part = new_str_hook_with_start_and_end(expression_str, i, expression_hook->end);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_str_hook(captured_element);
    free_str_hook(clean_string_value);
    return new_aio_string_result(value, rest_part);
}

static aio_result *make_plus(
        const_str_hook *expression_hook,
        const_aio_function_control_graph *control_graph
)
{
    const_string expression_string = expression_hook->source_string;
    aio_result *left_result = make_parentheses(expression_hook, control_graph, cast_to_string, make_string);
    aio_value *left_value = left_result->value;
    if (!left_value) {
        throw_error_with_hook(AIO_STRING_PARSER_TAG, "Found null in expression:", expression_hook);
    }
    str_hook *left_hook = new_str_hook_by_other(left_result->rest);
    const_string first_string_term = left_value->get.string_acc;
    //Create string builder:
    string_builder *str_builder = new_string_builder();
    append_string(str_builder, first_string_term);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_aio_result(left_result);
    //------------------------------------------------------------------------------------------------------------------
    while (is_not_empty_hooked_str(left_hook)) {
        const char symbol = expression_string[left_hook->start];
        //Check symbol:
        const_boolean is_plus = is_tilde_sign(symbol);
        if (is_plus) {
            //Create after sign part:
            str_hook *next_hook = new_str_hook(expression_string);
            next_hook->start = left_hook->start + 1;
            next_hook->end = left_hook->end;
            //Find value after sign part:
            aio_result *right_result = make_parentheses(next_hook, control_graph, cast_to_string, make_string);
            aio_value *right_value = right_result->value;
            if (!right_value) {
                throw_error_with_hook(AIO_STRING_PARSER_TAG, "Found null in expression:", next_hook);
            }
            const_string right_acc = right_result->value->get.string_acc;
            //Put right term in string builder:
            append_string(str_builder, right_acc);
            const_str_hook *old_left_hook = left_hook;
            left_hook = new_str_hook_by_other(right_result->rest);
            //----------------------------------------------------------------------------------------------------------
            //찌꺼기 수집기 (Garbage collector):
            free_str_hook(next_hook);
            free_aio_result(right_result);
            free_const_str_hook(old_left_hook);
            //----------------------------------------------------------------------------------------------------------
        } else {
            break;
        }
    }
    string new_string = pop_string_from_builder(str_builder);
    str_hook *rest = new_str_hook_by_other(left_hook);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_str_hook(left_hook);
    free_string_builder(str_builder);
    //------------------------------------------------------------------------------------------------------------------
    return new_aio_string_result(new_string, rest);
}

aio_value *parse_string_value_string(
        const_str_hook *expression_hook,
        const_aio_function_control_graph *control_graph
)
{
    aio_result *result = make_plus(expression_hook, control_graph);
    if (is_not_empty_hooked_str(result->rest)) {
        throw_error_with_tag(AIO_STRING_PARSER_TAG, "Can not fully parse expression!");
    }
    const_string result_string_acc = result->value->get.string_acc;
    aio_value *string_value = new_aio_string_value(result_string_acc);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_aio_result(result);
    return string_value;
}