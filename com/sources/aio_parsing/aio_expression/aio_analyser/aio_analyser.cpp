//lang:
#include <aio_lang/aio_types/aio_types.h>
#include <aio_lang/aio_modifiers/aio_modifiers.h>
//parsing:
#include <aio_parsing/aio_expression/aio_expression_parser.h>
//lib4aio:
#include <lib4aio_cpp_headers/aio_explorer/aio_explorer.h>
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/point_watcher/point_watcher.h>

#define AIO_EXPRESSION_PARSER_ERROR_TAG "AIO_EXPRESSION_PARSER_ERROR"

static const bool is_explicitly_boolean_expression(const str_hook *hooked_expression)
{
    bool result = false;
    const char *expression_string = hooked_expression->get_string();
    point_watcher *watcher = new point_watcher();
    //Configure borders:
    watcher->start = hooked_expression->start;
    watcher->pointer = hooked_expression->start;
    watcher->end = hooked_expression->end;
    //Init scopes:
    int parenthesis_scope_counter = 0;
    bool in_quote_scope = false;
    //Scanning:
    while (watcher->pointer < watcher->end) {
        const char symbol = expression_string[watcher->pointer];
        //Check symbol:
        const bool is_opening_parenthesis_cond = is_opening_parenthesis(symbol);
        const bool is_closing_parenthesis_cond = is_closing_parenthesis(symbol);
        const bool is_quote = is_single_quote(symbol);
        const bool is_boolean_symbol =
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
                throw_error_with_tag(
                        AIO_EXPRESSION_PARSER_ERROR_TAG,
                        "Expression can not start with closing parenthesis!"
                );
            }
        }
        if (is_boolean_symbol && parenthesis_scope_counter == 0 && !in_quote_scope) {
            result = true;
            break;
        }
        watcher->pointer++;
    }
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete watcher;
    //------------------------------------------------------------------------------------------------------------------
    return result;
}

static const str_hook *define_type_by_first_element(
        const str_hook *hooked_expression,
        aio_ray *control_graph
)
{
    const char *expression_string = hooked_expression->get_string();
    str_hook *scope = new str_hook(hooked_expression);
    unsigned pointer = hooked_expression->start;
    while (is_opening_parenthesis(expression_string[pointer])) {
        //We cannot define type by first element -> find the next element in the expression:
        str_hook *new_parenthesis_scope = aio_explorer::explore_hook_scope(
                pointer,
                '(',
                ')',
                scope
        );
        str_hook *old_scope = scope;
        const unsigned end_index = old_scope->end;
        scope = new_parenthesis_scope;
        //--------------------------------------------------------------------------------------------------------------
        delete old_scope;
        //--------------------------------------------------------------------------------------------------------------
        //Init next scope hook:
        const bool have_not_elements_on_this_level = scope->end == end_index;
        if (have_not_elements_on_this_level) {
            //There aren't elements on top level & define type by lower level:
            pointer = ++scope->start;
            scope->end--;
        } else {
            const unsigned after_parenthesis_position = pointer;
            const bool is_sign_after_closing_parenthesis = is_sign(expression_string[after_parenthesis_position]);
            if (is_sign_after_closing_parenthesis) {
                scope->start = after_parenthesis_position + 1;
            } else {
                throw_error_with_tag(AIO_EXPRESSION_PARSER_ERROR_TAG, "Expected sign after closing parenthesis");
            }
        }
        if (scope->start >= scope->end) {
            throw_error_with_tag(AIO_EXPRESSION_PARSER_ERROR_TAG, "Expression contains empty parentheses!");
        }
    }
    str_hook *scope_hook = new str_hook(scope);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete scope;
    //------------------------------------------------------------------------------------------------------------------
    str_hook *first_element_hook = nullptr;
    //Prepare to find first element of expression:
    bool in_quote_scope = false;
    point_watcher *element_watcher = new point_watcher();
    element_watcher->pointer = scope_hook->start;
    element_watcher->end = scope_hook->end;
    while (element_watcher->pointer < element_watcher->end) {
        const char symbol = expression_string[element_watcher->pointer];
        const bool is_whitespace_cond = is_space_or_line_break(symbol);
        const bool is_quote_cond = is_single_quote(symbol);
        if (is_quote_cond) {
            in_quote_scope = !in_quote_scope;
        }
        if (element_watcher->mode == point_watcher::POINT_WATCHER_PASSIVE_MODE && !is_whitespace_cond) {
            element_watcher->start = element_watcher->pointer;
            element_watcher->mode = point_watcher::POINT_WATCHER_ACTIVE_MODE;
        }
        if (element_watcher->mode == point_watcher::POINT_WATCHER_ACTIVE_MODE) {
            const bool is_end_of_element = (is_sign(symbol) || is_opening_parenthesis(symbol)) && !in_quote_scope;
            if (is_end_of_element) {
                element_watcher->end = element_watcher->pointer;
                first_element_hook = new str_hook(expression_string, element_watcher);
                break;
            }
        }
        element_watcher->pointer++;
    }
    //Check element hook:
    if (!first_element_hook) {
        first_element_hook = new str_hook(scope_hook);
    }
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete element_watcher;
    delete scope_hook;
    //------------------------------------------------------------------------------------------------------------------
    //Maybe is variable name?
//    const_aio_variable *variable = get_aio_variable_in_function_control_graph(first_element_hook, control_graph);
//    if (variable) {
//        str_hook *detected_type = NULL;
//        const_aio_variable_definition *definition = variable->definition;
//        const_boolean is_null_value = !variable->value;
//        if (is_null_value) {
//            detected_type = new_str_hook_by_string(VOID);
//        } else {
//            const_str_hook *required_type = definition->type;
//            const_boolean is_void_type = is_aio_void_type_hooked(required_type);
//            if (is_void_type) {
//                //Get value type from void:
//                detected_type = new_str_hook_by_other(variable->value->type);
//            } else {
//                detected_type = new_str_hook_by_other(required_type);
//            }
//        }
//        return detected_type;
//    }
    //Maybe is function?
//    const_aio_function_definition_list *definition_list = control_graph->context_ref->function_manager->definition_list;
//    const_aio_function_definition *definition = get_aio_function_definition_in_list_by_name(
//            definition_list,
//            first_element_hook
//    );
//    if (definition) {
//        const_str_hook_list *output_type_list = definition->output_type_list;
//        const_boolean is_single_return = output_type_list->size == 1;
//        if (is_single_return) {
//            return new_str_hook_by_other(output_type_list->hooks[0]);
//        } else {
//            throw_error_with_tag(AIO_EXPRESSION_PARSER_TAG, "Function must return single type!");
//        }
//    }
    if (first_element_hook->matches_int()) {
        return new str_hook(INTEGER);
    } else if (first_element_hook->matches_double()) {
        return new str_hook(DOUBLE);
    } else if (first_element_hook->matches_string()) {
        return new str_hook(STRING);
    } else if (first_element_hook->matches_boolean()) {
        return new str_hook(BOOLEAN);
    } else {
        throw_error_with_tag(AIO_EXPRESSION_PARSER_ERROR_TAG, "Can not define type of expression!");
    }
}

const str_hook *aio_expression_parser::aio_analyser::define_expression_type(
        const str_hook *expression_hook,
        aio_ray *control_graph
)
{
    const str_hook *type = nullptr;
    //Maybe is explicitly boolean expression?
    const bool is_boolean_expression = is_explicitly_boolean_expression(expression_hook);
    if (is_boolean_expression) {
        type = new str_hook(BOOLEAN);
    } else {
        //Define by first element:
        type = define_type_by_first_element(expression_hook, control_graph);
    }
    return type;
}