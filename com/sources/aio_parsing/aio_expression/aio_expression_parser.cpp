//runtime:
#include <aio_runtime/aio_ray/aio_ray.h>
#include <aio_runtime/aio_value/aio_value.h>
#include <aio_parsing/aio_expression/aio_expression_parser.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <aio_lang/aio_types/aio_types.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>

#define AIO_EXPRESSION_PARSER_ERROR_TAG "AIO_EXPRESSION_PARSER_ERROR"

aio_value *aio_expression_parser::parse(const char *expression, aio_ray *ray)
{
    //Define expression type:
    const str_hook *expression_hook = new str_hook(expression);
    aio_value *result = aio_expression_parser::parse(expression_hook, ray);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    delete expression_hook;
    //------------------------------------------------------------------------------------------------------------------
    return result;
}

aio_value *aio_expression_parser::parse(const str_hook *expression, aio_ray *ray)
{
    const str_hook *expression_type = aio_analyser::define_expression_type(expression, ray);
    const bool is_type_supported = is_aio_type_hooked(expression_type);
    aio_value *result = nullptr;
    if (is_type_supported) {
        if (is_aio_int_type_hooked(expression_type)) {
            //Parse int:
            result = aio_int_parser::parse(expression, ray);
        } else if (is_aio_double_type_hooked(expression_type)) {
            //Parse double:
            result = aio_double_parser::parse(expression, ray);
        } else if (is_aio_string_type_hooked(expression_type)) {
            //Parse string:
            result = aio_string_parser::parse(expression, ray);
        } else if (is_aio_boolean_type_hooked(expression_type)) {
            //Parse boolean:
            result = aio_boolean_parser::parse(expression, ray);
        } else {
            //Parse type:
            throw_error_with_tag(AIO_EXPRESSION_PARSER_ERROR_TAG, "AIO hasn't implemented this type yet!");
        }
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        delete expression_type;
        //--------------------------------------------------------------------------------------------------------------
        return result;
    } else {
        throw_error_with_str_hook(AIO_EXPRESSION_PARSER_ERROR_TAG, "AIO core doesn't support type:", expression_type);
    }
}