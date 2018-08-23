
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

#endif

#define AIO_STRING_PARSER_TAG "AIO_STRING_PARSER"

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

static aio_result *make_plus(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
#ifdef AIO_STRING_PARSER_DEBUG
    log_info_str_hook(AIO_STRING_PARSER_TAG, "Make plus with expression:", expression_hook);
#endif
    const_string expression_string = expression_hook->source_ref;
    aio_result *left_result = make_parentheses(expression_hook, context, control_graph, cast_to_string, make_string);
#ifdef AIO_STRING_PARSER_DEBUG
    log_info_str_hook(AIO_STRING_PARSER_TAG, "After plus rest:", left_result->rest);
#endif
    //Create string builder:
    string_builder *str_builder = new_string_builder();
    append_string(str_builder, left_result->value->get.string_acc);
    while (is_not_empty_hooked_str(left_result->rest)) {
        const char symbol = expression_string[left_result->rest->start];
        //Check symbol:
        if (is_tilde_sign(symbol)) {
            //Create after sign part:
            str_hook *next_hook = new_str_hook(expression_string);
            next_hook->start = left_result->rest->start + 1;
            next_hook->end = left_result->rest->end;
            //Find value after sign part:
            aio_result *right_result = make_parentheses(next_hook, context, control_graph, cast_to_string, make_string);
            const_string right_acc = right_result->value->get.string_acc;
#ifdef AIO_STRING_PARSER_DEBUG
            log_info_str_hook(AIO_STRING_PARSER_TAG, "AFTER LEFT REST:", right_result->rest);
#endif
            append_string(str_builder, right_acc);
            left_result->rest = new_str_hook_by_other(right_result->rest);
        }
    }
    string new_string = pop_string_from_builder(str_builder);
    return new_aio_string_result(new_string, new_str_hook_by_other(left_result->rest));
}

aio_value *parse_string_value_string(
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