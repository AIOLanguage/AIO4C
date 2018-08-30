#include <mem.h>
#include <lib/utils/boolean_utils/boolean_utils.h>
#include <lib/utils/str_hook/str_hook.h>
#include <lib/utils/string_utils/string_utils.h>
#include <lib/utils/point_watcher/point_watcher.h>
#include <lib/utils/char_utils/char_utils.h>
#include <lib/utils/error_utils/error_utils.h>
#include <tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <tools/aio_common_tools/aio_block_body_explorer/aio_block_body_explorer.h>
#include <lang/aio_function/aio_variable/aio_definition/aio_variable_definition.h>
#include <tools/aio_function_tools/aio_control_graph/aio_function_control_graph_management.h>
#include <lang/aio_function/aio_variable/aio_variable.h>
#include <lang/aio_type/aio_type.h>
#include <lang/aio_function/aio_function_definition/aio_function_definition.h>
#include <lang/aio_function/aio_value/aio_value.h>
#include <tools/aio_function_tools/aio_expression_parser/aio_expression_parser.h>
#include <lang/aio_context/aio_context.h>

#define AIO_EXPRESSION_PARSER_DEBUG

#define AIO_EXPRESSION_PARSER_TAG "AIO_EXPRESSION_PARSER"

static const_boolean is_explicitly_boolean_expression(const_str_hook *hooked_expression)
{
    boolean result = FALSE;
    const_string expression_string = hooked_expression->source_string;
    point_watcher *watcher = new_point_watcher();
    //Configure borders:
    watcher->start = hooked_expression->start;
    watcher->pointer = hooked_expression->start;
    watcher->end = hooked_expression->end;
    //Init scopes:
    int parenthesis_scope_counter = 0;
    boolean in_quote_scope = FALSE;
    //Scanning:
    while (watcher->pointer < watcher->end) {
        const char symbol = expression_string[watcher->pointer];
        //Check symbol:
        const_boolean is_opening_parenthesis_cond = is_opening_parenthesis(symbol);
        const_boolean is_closing_parenthesis_cond = is_closing_parenthesis(symbol);
        const_boolean is_quote = is_single_quote(symbol);
        const_boolean is_boolean_symbol =
                is_more_sign(symbol)
                || is_less_sign(symbol)
                || is_equal_sign(symbol)
                || is_and_sign(symbol)
                || is_or_sign(symbol)
                || is_exclamation_point(symbol);
        if (is_quote) {
            in_quote_scope = !in_quote_scope;
        }
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
        if (is_boolean_symbol && parenthesis_scope_counter == 0 && !in_quote_scope) {
            result = TRUE;
            break;
        }
        watcher->pointer++;
    }
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_point_watcher(watcher);
    //------------------------------------------------------------------------------------------------------------------
    return result;
}

static const_str_hook *define_type_by_first_element(
        const_str_hook *hooked_expression,
        const_aio_function_control_graph *control_graph
)
{
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
        } else {
            const int after_parenthesis_position = scope_watcher->pointer;
            const_boolean is_sign_after_closing_parenthesis = is_sign(expression_string[after_parenthesis_position]);
            if (is_sign_after_closing_parenthesis) {
                scope_watcher->start = after_parenthesis_position + 1;
            } else {
                throw_error_with_tag(AIO_EXPRESSION_PARSER_TAG, "Expected sign after closing parenthesis");
            }
        }
        if (scope_watcher->start >= scope_watcher->end) {
            throw_error_with_tag(AIO_EXPRESSION_PARSER_TAG, "Expression contains empty parentheses!");
        }
    }
    str_hook *scope_hook = new_str_hook_by_point_watcher(expression_string, scope_watcher);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_point_watcher(scope_watcher);
    //------------------------------------------------------------------------------------------------------------------
    str_hook *first_element_hook = NULL;
    //Prepare to find first element of expression:
    boolean in_quote_scope = FALSE;
    point_watcher *element_watcher = new_point_watcher();
    element_watcher->pointer = scope_hook->start;
    element_watcher->end = scope_hook->end;
    while (element_watcher->pointer < element_watcher->end) {
        const char symbol = expression_string[element_watcher->pointer];
        const_boolean is_whitespace_cond = is_space_or_line_break(symbol);
        const_boolean is_quote_cond = is_single_quote(symbol);
        if (is_quote_cond) {
            in_quote_scope = !in_quote_scope;
        }
        if (element_watcher->mode == POINT_WATCHER_PASSIVE_MODE && !is_whitespace_cond) {
            element_watcher->start = element_watcher->pointer;
            element_watcher->mode = POINT_WATCHER_ACTIVE_MODE;
        }
        if (element_watcher->mode == POINT_WATCHER_ACTIVE_MODE) {
            const_boolean is_end_of_element = (is_sign(symbol) || is_opening_parenthesis(symbol)) && !in_quote_scope;
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
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_point_watcher(element_watcher);
    free_str_hook(scope_hook);
    //------------------------------------------------------------------------------------------------------------------
    //Maybe is variable name?
    const_aio_variable *variable = get_aio_variable_in_function_control_graph(first_element_hook, control_graph);
    if (variable) {
        str_hook *detected_type = NULL;
        const_aio_variable_definition *definition = variable->definition;
        const_boolean is_null_value = !variable->value;
        if (is_null_value) {
            detected_type = new_str_hook_by_string(VOID);
        } else {
            const_str_hook *required_type = definition->type;
            const_boolean is_void_type = is_aio_void_type_hooked(required_type);
            if (is_void_type) {
                //Get value type from void:
                detected_type = new_str_hook_by_other(variable->value->type);
            } else {
                detected_type = new_str_hook_by_other(required_type);
            }
        }
        return detected_type;
    }
    //Maybe is function?
    const_aio_function_definition_list *definition_list = control_graph->context_ref->function_manager->definition_list;
    const_aio_function_definition *definition = get_aio_function_definition_in_list_by_name(
            definition_list,
            first_element_hook
    );
    if (definition) {
        const_str_hook_list *output_type_list = definition->output_type_list;
        const_boolean is_single_return = output_type_list->size == 1;
        if (is_single_return) {
            return new_str_hook_by_other(output_type_list->hooks[0]);
        } else {
            throw_error_with_tag(AIO_EXPRESSION_PARSER_TAG, "Function must return single type!");
        }
    }
    if (is_null_hooked(first_element_hook)) {
        return new_str_hook_by_string(VOID);
    } else if (is_int_hooked(first_element_hook)) {
        return new_str_hook_by_string(INTEGER);
    } else if (is_double_hooked(first_element_hook)) {
        return new_str_hook_by_string(DOUBLE);
    } else if (is_string_hooked(first_element_hook)) {
        return new_str_hook_by_string(STRING);
    } else if (is_boolean_hooked(first_element_hook)) {
        return new_str_hook_by_string(BOOLEAN);
    } else {
        throw_error_with_tag(AIO_EXPRESSION_PARSER_TAG, "Can not define type of expression!");
    }
}

static const_str_hook *define_expression_type(
        const_str_hook *expression_hook,
        const_aio_function_control_graph *control_graph
)
{
    const_str_hook *type = NULL;
    //Maybe is explicitly boolean expression?
    const_boolean is_boolean_expression = is_explicitly_boolean_expression(expression_hook);
    if (is_boolean_expression) {
        type = new_str_hook_by_string(BOOLEAN);
    } else {
        //Define by first element:
        type = define_type_by_first_element(expression_hook, control_graph);
    }
    return type;
}

/**
 * Parses expression hook.
 * @param expression_hook
 * @param control_graph
 * @return value.
 */

aio_value *parse_value_hook(
        const_str_hook *expression_hook,
        const_aio_function_control_graph *control_graph
)
{
    const_str_hook *expression_type = define_expression_type(expression_hook, control_graph);
    const_boolean is_type_supported = is_aio_type_hooked(expression_type);
    aio_value *result = NULL;
    if (is_type_supported) {
        if (is_aio_void_type_hooked(expression_type)) {
            //Parse void:
            result = parse_void_value_string(expression_hook, control_graph);;
        } else if (is_aio_int_type_hooked(expression_type)) {
            //Parse int:
            result = parse_int_value_string(expression_hook, control_graph);
        } else if (is_aio_double_type_hooked(expression_type)) {
            //Parse double:
            result = parse_double_value_string(expression_hook, control_graph);
        } else if (is_aio_string_type_hooked(expression_type)) {
            //Parse string:
            result = parse_string_value_string(expression_hook, control_graph);
        } else if (is_aio_boolean_type_hooked(expression_type)) {
            //Parse boolean:
            result = parse_boolean_value_string(expression_hook, control_graph);
        } else {
            //Parse type:
            result = parse_type_value_string(expression_hook, control_graph);
        }
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_const_str_hook(expression_type);
        //--------------------------------------------------------------------------------------------------------------
        return result;
    } else {
        throw_error_with_hook(AIO_EXPRESSION_PARSER_TAG, "AIO core doesn't support type:", expression_type);
    }
}

/**
 * Parses string expression.
 * @param expression_string
 * @param control_graph
 * @return value.
 */

aio_value *parse_value_string(
        const_string expression_string,
        const_aio_function_control_graph *control_graph
)
{
    //Define expression type:
    str_hook *expression_hook = new_str_hook_by_string(expression_string);
    aio_value *result = parse_value_hook(expression_hook, control_graph);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_str_hook(expression_hook);
    //------------------------------------------------------------------------------------------------------------------
    return result;
}