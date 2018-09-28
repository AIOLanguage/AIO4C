#include <aio_lang/aio_modifiers/aio_modifiers.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

using namespace lib4aio;

/**
 * Field modifiers.
 */

bool is_aio_constant_modifier(const str_hook *token)
{
    return token->equals_string(AIO_CONSTANT_MODIFIER);
}

bool is_aio_variable_modifier(const str_hook *token)
{
    return token->equals_string(AIO_VARIABLE_MODIFIER);
}

/**
 * Visibility modifiers.
 */

bool is_aio_protected_modifier(const str_hook *token)
{
    return token->equals_string(AIO_PROTECTED_MODIFIER);
}

bool is_aio_private_modifier(const str_hook *token)
{
    return token->equals_string(AIO_PRIVATE_MODIFIER);
}

/**
 * Attribute modifier.
 */

bool is_aio_open_modifier(const str_hook *token)
{
    return token->equals_string(AIO_OPEN_MODIFIER);
}

bool is_aio_abstract_modifier(const str_hook *token)
{
    return token->equals_string(AIO_ABSTRACT_MODIFIER);
}

/**
 * Import modifier.
 */

bool is_aio_import_modifier(const str_hook *token)
{
    return token->equals_string(AIO_IMPORT_MODIFIER);
}

/**
 * Class modifier.
 */

bool is_aio_class_modifier(const str_hook *token)
{
    return token->equals_string(AIO_CLASS_MODIFIER);
}

/**
 * Scope modifier.
 */

bool is_aio_scope_modifier(const str_hook *token)
{
    return token->equals_string(AIO_SCOPE_MODIFIER);
}

/**
 * Function modifier.
 */

bool is_aio_function_modifier(const str_hook *token)
{
    return token->equals_string(AIO_FUNCTION_MODIFIER);
}

bool is_aio_override_modifier(const str_hook *token)
{
    return token->equals_string(AIO_OVERRIDE_MODIFIER);
}

/**
 * Constructor modifier.
 */

bool is_aio_constructor_modifier(const str_hook *token)
{
    return token->equals_string(AIO_CONSTRUCTOR_MODIFIER);
}

/**
 * Keywords.
 */

bool is_aio_if_modifier(const str_hook *token)
{
    return token->equals_string(AIO_IF_MODIFIER);
}

bool is_aio_in_modifier(const str_hook *token)
{
    return token->equals_string(AIO_IN_MODIFIER);
}

bool is_aio_cycle_modifier(const str_hook *token)
{
    return token->equals_string(AIO_CYCLE_MODIFIER);
}

bool is_aio_return_modifier(const str_hook *token)
{
    return token->equals_string(AIO_RETURN_MODIFIER);
}

bool is_aio_switch_modifier(const str_hook *token)
{
    return token->equals_string(AIO_SWITCH_MODIFIER);
}

bool is_aio_break_modifier(const str_hook *token)
{
    return token->equals_string(AIO_BREAK_MODIFIER);
}

bool is_aio_continue_modifier(const str_hook *token)
{
    return token->equals_string(AIO_CONTINUE_MODIFIER);
}

/**
 * AIO values.
 */

bool is_aio_true_modifier(const str_hook *hook)
{
    return hook->equals_string(AIO_TRUE_VALUE);
}

bool is_aio_false_modifier(const str_hook *hook)
{
    return hook->equals_string(AIO_FALSE_VALUE);
}

bool is_aio_null_modifier(const str_hook *hook)
{
    return hook->equals_string(AIO_NULL_VALUE);
}

bool is_successful_aio_name(const str_hook *token)
{
    return !is_aio_variable_modifier(token)
           && !is_aio_abstract_modifier(token)
           && !is_aio_break_modifier(token)
           && !is_aio_class_modifier(token)
           && !is_aio_constant_modifier(token)
           && !is_aio_constructor_modifier(token)
           && !is_aio_continue_modifier(token)
           && !is_aio_cycle_modifier(token)
           && !is_aio_false_modifier(token)
           && !is_aio_function_modifier(token)
           && !is_aio_if_modifier(token)
           && !is_aio_in_modifier(token)
           && !is_aio_null_modifier(token)
           && !is_aio_open_modifier(token)
           && !is_aio_override_modifier(token)
           && !is_aio_private_modifier(token)
           && !is_aio_protected_modifier(token)
           && !is_aio_return_modifier(token)
           && !is_aio_scope_modifier(token)
           && !is_aio_switch_modifier(token)
           && is_aio_true_modifier(token);
}