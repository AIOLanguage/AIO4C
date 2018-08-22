#include <mem.h>
#include "../../../../headers/lang/aio_function/aio_value/aio_value.h"
#include "../../../../headers/lang/aio_context/aio_context.h"
#include "../../../../headers/lib/utils/point_watcher/point_watcher.h"
#include "../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lang/aio_type/aio_type.h"
#include "../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"

#define AIO_EXPRESSION_PARSER_DEBUG

#define AIO_EXPRESSION_PARSER_TAG "AIO_EXPRESSION_PARSER"

static const_boolean is_explicitly_boolean_expression(const_str_hook *hooked_expression)
{
    const int expression_length = get_str_hook_size(hooked_expression);
    const_string expression_string = hooked_expression->source_ref;
    point_watcher *watcher = new_point_watcher();
    int parenthesis_scope_counter = 0;
    while (watcher->pointer < expression_length) {
        const char symbol = expression_string[watcher->pointer];
        //Check symbol:
        const_boolean is_opening_parenthesis_cond = is_opening_parenthesis(symbol);
        const_boolean is_closing_parenthesis_cond = is_closing_parenthesis(symbol);
        const_boolean is_boolean_symbol =
                is_more_sign(symbol)
                || is_less_sign(symbol)
                || is_equal_sign(symbol)
                || is_and_sign(symbol)
                || is_or_sign(symbol);
        if (is_opening_parenthesis_cond) {
            parenthesis_scope_counter++;
        }
        if (is_closing_parenthesis_cond) {
            if (parenthesis_scope_counter > 0) {
                parenthesis_scope_counter--;
            } else {
                throw_error_with_tag(AIO_EXPRESSION_PARSER_TAG, "Expression can not start with closing parenthesis!");
            }
        }
        if (is_boolean_symbol && parenthesis_scope_counter == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

static const_str_hook *define_type_by_first_element(
        const_str_hook *hooked_expression,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    str_hook *first_element_hook = NULL;
    //Prepare to find first element of expression:
    const int expression_length = get_str_hook_size(hooked_expression);
    const_string expression_string = hooked_expression->source_ref;
    point_watcher *watcher = new_point_watcher();
    while (watcher->pointer < expression_length) {
        const char symbol = expression_string[watcher->pointer];
        const_boolean is_whitespace_cond = is_space_or_line_break(symbol);
        if (watcher->mode == POINT_WATCHER_PASSIVE_MODE && !is_whitespace_cond) {
            watcher->start = watcher->pointer;
            watcher->mode = POINT_WATCHER_ACTIVE_MODE;
        }
        if (watcher->mode == POINT_WATCHER_ACTIVE_MODE) {
            const_boolean is_end_of_element = is_whitespace_cond || is_sign(symbol) || is_opening_parenthesis(symbol);
            if (is_end_of_element) {
                first_element_hook = new_str_hook_by_point_watcher(expression_string, watcher);
                break;
            }
        }
        watcher->pointer++;
    }
    //Check element hook:
    if (first_element_hook != NULL) {
        //Maybe is variable name?
        const_aio_variable *variable = get_aio_variable_in_function_control_graph(first_element_hook, control_graph);
        if (variable != NULL) {
            const_aio_variable_definition *definition = variable->definition;
            return new_str_hook_by_other(definition->type);
        }
        //Maybe is function?
        const_aio_function_definition_list *function_definition_list = context->function_manager->definition_list;
        const_aio_function_definition *function_definition = get_aio_function_definition_in_list_by_name(
                function_definition_list, first_element_hook
        );
        if (function_definition != NULL) {
            const_str_hook_list *output_type_list = function_definition->output_type_list;
            const_boolean is_single_return = output_type_list->size == 1;
            if (is_single_return) {
                return new_str_hook_by_other(output_type_list->hooks[0]);
            } else {
                throw_error_with_tag(AIO_EXPRESSION_PARSER_TAG, "function must return single type!");
            }
        }
        //Maybe int value?
        if (is_int_hooked(first_element_hook)) {
            return new_str_hook_by_string(INTEGER);
        }
        //Maybe double value?
        if (is_double_hooked(first_element_hook)) {
            return new_str_hook_by_string(DOUBLE);
        }
        //Maybe string value?
        if (is_string_hooked(first_element_hook)) {
            return new_str_hook_by_string(STRING);
        }
        //Maybe boolean value?
        if (is_boolean_hooked(first_element_hook)) {
            return new_str_hook_by_string(BOOLEAN);
        } else {
            throw_error_with_tag(AIO_EXPRESSION_PARSER_TAG, "Can not define type of expression!");
        }
    } else {
        throw_error_with_tag(AIO_EXPRESSION_PARSER_TAG, "Can not define first element in expression!");
    }
}

static const_str_hook *define_type(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    //Maybe is explicitly boolean expression?
    const_boolean is_boolean_expression = is_explicitly_boolean_expression(expression_hook);
    if (is_boolean_expression) {
        return new_str_hook_by_string(BOOLEAN);
    }
    //Define by first element:
    return define_type_by_first_element(expression_hook, context, control_graph);
}

aio_value *parse_value_hook(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    const_str_hook *expression_type = define_type(expression_hook, context, control_graph);
    if (!is_aio_type_hooked(expression_type)) {
        throw_error_with_hook(AIO_EXPRESSION_PARSER_TAG, "AIO core doesn't support type:", expression_type);
    }
    //Maybe is boolean?
    if (is_hook_equals_str(expression_hook, INTEGER)) {
        return parse_int_value_string(expression_hook, context, control_graph);
    }
    if (is_hook_equals_str(expression_hook, DOUBLE)) {
        return parse_double_value_string(expression_hook, context, control_graph);
    }
    if (is_hook_equals_str(expression_hook, STRING)) {
        return parse_string_value_string(expression_hook, context, control_graph);
    }
    if (is_hook_equals_str(expression_hook, BOOLEAN)) {
        return parse_boolean_value_string(expression_hook, context, control_graph);
    } else {
        return parse_type_value_string(expression_hook, context, control_graph);
    }
}

aio_value *parse_value_string(
        const_string expression_string,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    //Define expression type:
    const_str_hook *expression_hook = new_str_hook_by_string(expression_string);
    return parse_value_hook(expression_hook, context, control_graph);
}