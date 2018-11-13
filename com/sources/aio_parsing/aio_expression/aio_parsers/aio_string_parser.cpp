//lang:
#include <aio_lang/aio_modifiers/aio_modifiers.h>
//parsing:
#include <aio_parsing/aio_expression/aio_expression_parser.h>
//runtime:
#include <aio_runtime/aio_value/aio_value.h>
#include <aio_runtime/aio_result/aio_result.h>
#include <aio_runtime/aio_value/advanced_functions/cast_aio_value.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/str_builder/str_builder.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define AIO_STRING_PARSER_DEBUG

#ifdef AIO_STRING_PARSER_DEBUG

#endif

#define AIO_STRING_PARSER_INFO_TAG "AIO_STRING_PARSER_INFO"

aio_value *aio_expression_parser::aio_string_parser::parse(
        const str_hook *expression_hook,
        aio_ray *control_graph
)
{
    aio_result *result = aio_string_parser::make_plus(expression_hook, control_graph);
    if (result->rest->is_not_empty()) {
        throw_error_with_tag(AIO_STRING_PARSER_INFO_TAG, "Can not fully parse expression!");
    }
    const char *result_string_acc = result->value->get.string_acc;
    aio_value *string_value = new_aio_string_value(result_string_acc);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete result;
    //------------------------------------------------------------------------------------------------------------------
    return string_value;
}

aio_result *aio_expression_parser::aio_string_parser::make_plus(
        const str_hook *expression_hook,
        aio_ray *control_graph
)
{
    const char *expression_string = expression_hook->get_string();
    aio_result *left_result = aio_assistant::make_parentheses(
            expression_hook,
            control_graph,
            cast_to_string,
            make_string
    );
    aio_value *left_value = left_result->value;
    if (!left_value) {
        throw_error_with_str_hook(AIO_STRING_PARSER_INFO_TAG, "Found null in expression:", expression_hook);
    }
    str_hook *left_hook = new str_hook(left_result->rest);
    const char *first_string_term = left_value->get.string_acc;
    //Create string builder:
    str_builder *builder = new str_builder();
    builder->append(first_string_term);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete left_result;
    //------------------------------------------------------------------------------------------------------------------
    while (true) {
        const char symbol = expression_string[left_hook->start];
        //Check symbol:
        const bool is_plus = is_tilde_sign(symbol);
        if (is_plus) {
            //Create after sign part:
            str_hook *next_hook = new str_hook(expression_string);
            next_hook->start = left_hook->start + 1;
            next_hook->end = left_hook->end;
            //Find value after sign part:
            aio_result *right_result = aio_assistant::make_parentheses(
                    next_hook,
                    control_graph,
                    cast_to_string,
                    make_string
            );
            aio_value *right_value = right_result->value;
            if (!right_value) {
                throw_error_with_str_hook(AIO_STRING_PARSER_INFO_TAG, "Found null in expression:", next_hook);
            }
            const char *right_acc = right_result->value->get.string_acc;
            //Put right term in string builder:
            builder->append(right_acc);
            const str_hook *old_left_hook = left_hook;
            left_hook = new str_hook(right_result->rest);
            //----------------------------------------------------------------------------------------------------------
            //찌꺼기 수집기 (Garbage collector):
            delete next_hook;
            delete right_result;
            delete old_left_hook;
            //----------------------------------------------------------------------------------------------------------
        } else {
            break;
        }
    }
    char *new_string = builder->pop();
    str_hook *rest = new str_hook(left_hook);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete left_hook;
    delete builder;
    //------------------------------------------------------------------------------------------------------------------
    return new aio_result(new_string, rest);
}

aio_result *aio_expression_parser::aio_string_parser::make_string(const str_hook *expression_hook)
{
    const char *expression_str = expression_hook->get_string();
    unsigned i = expression_hook->start;
    while (!is_tilde_sign(expression_str[i]) && i < expression_hook->end) {
        i++;
    }
    str_hook *captured_element = new str_hook(expression_str);
    captured_element->start = expression_hook->start;
    captured_element->end = i;
    str_hook *clean_string_value = NULL;
    if (is_aio_null_modifier(captured_element)) {
        throw_error_with_str_hook(AIO_STRING_PARSER_INFO_TAG, "Found null in expression:", expression_hook);
    } else if (captured_element->matches_int()
               || captured_element->matches_double()
               || captured_element->matches_boolean()) {
        clean_string_value = new str_hook(captured_element);
    } else if (captured_element->matches_string()) {
        const str_hook *naked_hook = captured_element->lower_quotes();
        clean_string_value = new str_hook(naked_hook);
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        delete naked_hook;
        //--------------------------------------------------------------------------------------------------------------
    } else {
        throw_error_with_tag(AIO_STRING_PARSER_INFO_TAG, "Cannot define type of expression!");
    }
    char *value = clean_string_value->to_string();
    str_hook *rest_part = new str_hook(expression_str, i, expression_hook->end);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete (captured_element);
    delete (clean_string_value);
    //------------------------------------------------------------------------------------------------------------------
    return new aio_result(value, rest_part);
}