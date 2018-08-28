#include <mem.h>
#include "../../../../headers/lang/aio_function/aio_value/aio_value.h"
#include "../../../../headers/lang/aio_context/aio_context.h"
#include "../../../../headers/lib/utils/point_watcher/point_watcher.h"
#include "../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lang/aio_type/aio_type.h"
#include "../../../../headers/tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h"
#include "../../../../headers/lib/utils/log_utils/log_utils.h"
#include "../../../../headers/tools/aio_common_tools/aio_block_body_explorer/aio_block_body_explorer.h"

#define AIO_EXPRESSION_PARSER_DEBUG

#define AIO_EXPRESSION_PARSER_TAG "AIO_EXPRESSION_PARSER"

static const_boolean is_explicitly_boolean_expression(const_str_hook *hooked_expression)
{
    const_string expression_string = hooked_expression->source_string;
    point_watcher *watcher = new_point_watcher();
    watcher->start = hooked_expression->start;
    watcher->pointer = hooked_expression->start;
    watcher->end = hooked_expression->end;
    int parenthesis_scope_counter = 0;
    while (watcher->pointer < watcher->end) {
        const char symbol = expression_string[watcher->pointer];
        //Check symbol:
        const_boolean is_opening_parenthesis_cond = is_opening_parenthesis(symbol);
        const_boolean is_closing_parenthesis_cond = is_closing_parenthesis(symbol);
        const_boolean is_boolean_symbol =
                is_more_sign(symbol)
                || is_less_sign(symbol)
                || is_equal_sign(symbol)
                || is_and_sign(symbol)
                || is_or_sign(symbol)
                || is_exclamation_point(symbol);
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
#ifdef AIO_EXPRESSION_PARSER_DEBUG
            log_info(AIO_EXPRESSION_PARSER_TAG, "Found boolean symbol -> is explicitly boolean expression!");
#endif
            return TRUE;
        }
        watcher->pointer++;
    }
    return FALSE;
}

static const_str_hook *define_type_by_first_element(
        const_str_hook *hooked_expression,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
#ifdef AIO_EXPRESSION_PARSER_DEBUG
    log_info_str_hook(AIO_EXPRESSION_PARSER_TAG, "Define type by first element in expression:", hooked_expression);
#endif
    const_string expression_string = hooked_expression->source_string;
    const int start_index = hooked_expression->start;
    const int end_index = hooked_expression->end;
    //Define left & right searching bounds:
    point_watcher *scope_watcher = new_point_watcher();
    scope_watcher->start = start_index;
    scope_watcher->pointer = start_index;
    scope_watcher->end = end_index;
    while (is_opening_parenthesis(expression_string[scope_watcher->pointer])) {
        //We cannot define type by first element -> find the next element in the expression:
        explore_aio_header_bounds(expression_string, &scope_watcher->start, &scope_watcher->pointer);
        //Init next scope hook:
        const_boolean have_not_elements_on_this_level = scope_watcher->pointer == end_index;
        if (have_not_elements_on_this_level) {
            //There aren't elements on top level & define type by lower level:
            scope_watcher->pointer = ++scope_watcher->start;
            scope_watcher->end--;
#ifdef AIO_EXPRESSION_PARSER_DEBUG
            log_info(AIO_EXPRESSION_PARSER_TAG, "Decrease level scope...");
            log_info_int(AIO_EXPRESSION_PARSER_TAG, "Start:", scope_watcher->start);
            log_info_int(AIO_EXPRESSION_PARSER_TAG, "End:", scope_watcher->end);
            if (scope_watcher->start < scope_watcher->end) {
                const_str_hook *next_hook = new_str_hook_by_point_watcher(expression_string, scope_watcher);
                log_info_str_hook(AIO_EXPRESSION_PARSER_TAG, "Next hook:", next_hook);
                free_const_str_hook(next_hook);
            } else {
                log_info(AIO_EXPRESSION_PARSER_TAG, "Was intersection!");
            }
#endif
        } else {
            const int after_parenthesis_position = scope_watcher->pointer;
            const_boolean is_sign_after_closing_parenthesis = expression_string[after_parenthesis_position];
            if (is_sign_after_closing_parenthesis) {
                scope_watcher->start = after_parenthesis_position + 1;
            } else {
                throw_error_with_tag(AIO_EXPRESSION_PARSER_TAG, "Expected sign after closing parenthesis");
            }
#ifdef AIO_EXPRESSION_PARSER_DEBUG
            log_info(AIO_EXPRESSION_PARSER_TAG, "Shift left border...");
            log_info_int(AIO_EXPRESSION_PARSER_TAG, "Start:", scope_watcher->start);
            log_info_int(AIO_EXPRESSION_PARSER_TAG, "End:", scope_watcher->end);
#endif
        }
        if (scope_watcher->start >= scope_watcher->end) {
            throw_error_with_tag(AIO_EXPRESSION_PARSER_TAG, "Expression contains empty parentheses!");
        }
    }
    str_hook *scope_hook = new_str_hook_by_point_watcher(expression_string, scope_watcher);
#ifdef AIO_EXPRESSION_PARSER_DEBUG
    log_info_str_hook(AIO_EXPRESSION_PARSER_TAG, "Scope hook is ready:", scope_hook);
#endif
    str_hook *first_element_hook = NULL;
    //Prepare to find first element of expression:
    point_watcher *element_watcher = new_point_watcher();
    element_watcher->pointer = scope_hook->start;
    element_watcher->end = scope_hook->end;
    while (element_watcher->pointer < element_watcher->end) {
        const char symbol = expression_string[element_watcher->pointer];
        const_boolean is_whitespace_cond = is_space_or_line_break(symbol);
        if (element_watcher->mode == POINT_WATCHER_PASSIVE_MODE && !is_whitespace_cond) {
            element_watcher->start = element_watcher->pointer;
            element_watcher->mode = POINT_WATCHER_ACTIVE_MODE;
        }
        if (element_watcher->mode == POINT_WATCHER_ACTIVE_MODE) {
            //const_boolean is_end_of_element = is_whitespace_cond || is_sign(symbol) || is_opening_parenthesis(symbol);
            const_boolean is_end_of_element = is_sign(symbol) || is_opening_parenthesis(symbol);
            if (is_end_of_element) {
                element_watcher->end = element_watcher->pointer;
                first_element_hook = new_str_hook_by_point_watcher(expression_string, element_watcher);
                break;
            }
        }
        element_watcher->pointer++;
    }
    //Check element hook:
    if (!first_element_hook) {
        first_element_hook = new_str_hook_by_other(scope_hook);
    }
#ifdef AIO_EXPRESSION_PARSER_DEBUG
    log_info_str_hook(AIO_EXPRESSION_PARSER_TAG, "First element:", first_element_hook);
#endif
    //Maybe is variable name?
    const_aio_variable *variable = get_aio_variable_in_function_control_graph(first_element_hook, control_graph);
    if (variable) {
        const_aio_variable_definition *definition = variable->definition;
#ifdef AIO_EXPRESSION_PARSER_DEBUG
        log_info_str_hook(AIO_EXPRESSION_PARSER_TAG, "Found variable:", definition->name);
        log_info_str_hook(AIO_EXPRESSION_PARSER_TAG, "Type:", definition->type);
#endif
        if (!variable->value) {
            return new_str_hook_by_string(VOID);
        } else {
            const_str_hook *required_type = definition->type;
            const_boolean is_void_type = is_aio_void_type_hooked(required_type);
            if (is_void_type) {
                //Get value type:
                const_str_hook *real_type = variable->value->type;
                return new_str_hook_by_other(real_type);
            } else {
                return new_str_hook_by_other(required_type);
            }
        }
    }
#ifdef AIO_EXPRESSION_PARSER_DEBUG
    log_info(AIO_EXPRESSION_PARSER_TAG, "Didn't find variable!");
#endif
    //Maybe is function?
    const_aio_function_definition_list *function_definition_list = context->function_manager->definition_list;
    const_aio_function_definition *function_definition = get_aio_function_definition_in_list_by_name(
            function_definition_list, first_element_hook
    );
    if (function_definition) {
#ifdef AIO_EXPRESSION_PARSER_DEBUG
        log_info(AIO_EXPRESSION_PARSER_TAG, "Found function!");
#endif
        const_str_hook_list *output_type_list = function_definition->output_type_list;
        const_boolean is_single_return = output_type_list->size == 1;
        if (is_single_return) {
            return new_str_hook_by_other(output_type_list->hooks[0]);
        } else {
            throw_error_with_tag(AIO_EXPRESSION_PARSER_TAG, "Function must return single type!");
        }
    }
    //Maybe int value?
    if (is_null_hooked(first_element_hook)) {
        return new_str_hook_by_string(VOID);
    }
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
}

static const_str_hook *define_type(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    //Maybe is explicitly boolean expression?
#ifdef AIO_EXPRESSION_PARSER_DEBUG
    log_info(AIO_EXPRESSION_PARSER_TAG, "Start define expression type...");
#endif
    const_boolean is_boolean_expression = is_explicitly_boolean_expression(expression_hook);
#ifdef AIO_EXPRESSION_PARSER_DEBUG
    log_info_boolean(AIO_EXPRESSION_PARSER_TAG, "Is explicitly boolean expression:", is_boolean_expression);
#endif
    if (is_boolean_expression) {
        return new_str_hook_by_string(BOOLEAN);
    }
    //Define by first element:
#ifdef AIO_EXPRESSION_PARSER_DEBUG
    log_info(AIO_EXPRESSION_PARSER_TAG, "Define type by first element...");
#endif
    return define_type_by_first_element(expression_hook, context, control_graph);
}

aio_value *parse_value_hook(
        const_str_hook *expression_hook,
        const_aio_context *context,
        const_aio_function_control_graph *control_graph
)
{
    const_str_hook *expression_type = define_type(expression_hook, context, control_graph);
#ifdef AIO_EXPRESSION_PARSER_DEBUG
    log_info_str_hook(AIO_EXPRESSION_PARSER_TAG, "Found expression type:", expression_type);
#endif
    if (!is_aio_type_hooked(expression_type)) {
        throw_error_with_hook(AIO_EXPRESSION_PARSER_TAG, "AIO core doesn't support type:", expression_type);
    }
    if (is_hook_equals_str(expression_type, VOID)) {
#ifdef AIO_EXPRESSION_PARSER_DEBUG
        log_info(AIO_EXPRESSION_PARSER_TAG, "Parse void expression...");
        return parse_void_value_string(expression_hook, context, control_graph);
#endif
    }
    //Maybe is boolean?
    if (is_hook_equals_str(expression_type, INTEGER)) {
#ifdef AIO_EXPRESSION_PARSER_DEBUG
        log_info(AIO_EXPRESSION_PARSER_TAG, "Parse int expression...");
#endif
        return parse_int_value_string(expression_hook, context, control_graph);
    }
    if (is_hook_equals_str(expression_type, DOUBLE)) {
#ifdef AIO_EXPRESSION_PARSER_DEBUG
        log_info(AIO_EXPRESSION_PARSER_TAG, "Parse double expression...");
#endif
        return parse_double_value_string(expression_hook, context, control_graph);
    }
    if (is_hook_equals_str(expression_type, STRING)) {
#ifdef AIO_EXPRESSION_PARSER_DEBUG
        log_info(AIO_EXPRESSION_PARSER_TAG, "Parse string expression...");
#endif
        return parse_string_value_string(expression_hook, context, control_graph);
    }
    if (is_hook_equals_str(expression_type, BOOLEAN)) {
#ifdef AIO_EXPRESSION_PARSER_DEBUG
        log_info(AIO_EXPRESSION_PARSER_TAG, "Parse boolean expression...");
#endif
        return parse_boolean_value_string(expression_hook, context, control_graph);
    } else {
#ifdef AIO_EXPRESSION_PARSER_DEBUG
        log_info(AIO_EXPRESSION_PARSER_TAG, "Parse type expression...");
#endif
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
#ifdef AIO_EXPRESSION_PARSER_DEBUG
    log_info_str_hook(AIO_EXPRESSION_PARSER_TAG, "Expression:", expression_hook);
#endif
    return parse_value_hook(expression_hook, context, control_graph);
}