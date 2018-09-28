#ifndef AIO_MODIFIERS_H
#define AIO_MODIFIERS_H

namespace lib4aio {

    class str_hook;
}

using namespace lib4aio;

/**
 * Field modifiers.
 */

#define AIO_CONSTANT_MODIFIER "constant"

#define AIO_VARIABLE_MODIFIER "variable"

bool is_aio_constant_modifier(const str_hook *token);

bool is_aio_variable_modifier(const str_hook *token);

/**
 * Visibility modifiers.
 */

#define AIO_PROTECTED_MODIFIER "protected"

#define AIO_PRIVATE_MODIFIER "private"

bool is_aio_protected_modifier(const str_hook *token);

bool is_aio_private_modifier(const str_hook *token);

/**
 * Attribute modifier.
 */

#define AIO_OPEN_MODIFIER "open"

#define AIO_ABSTRACT_MODIFIER "abstract"

bool is_aio_open_modifier(const str_hook *token);

bool is_aio_abstract_modifier(const str_hook *token);

/**
 * Import modifier.
 */

#define AIO_IMPORT_MODIFIER "addition"

bool is_aio_import_modifier(const str_hook *token);

/**
 * Class modifier.
 */

#define AIO_CLASS_MODIFIER "typename"

/**
 * Enum modifier.
 */

#define AIO_ENUM_MODIFIER "enumname"

bool is_aio_class_modifier(const str_hook *token);

/**
 * Scope modifier.
 */

#define AIO_SCOPE_MODIFIER "partname"

bool is_aio_scope_modifier(const str_hook *token);

/**
 * Function  modifier.
 */

#define AIO_FUNCTION_MODIFIER "function"

#define AIO_OVERRIDE_MODIFIER "override"

bool is_aio_function_modifier(const str_hook *token);

bool is_aio_override_modifier(const str_hook *token);

/**
 * Constructor modifier.
 */

bool is_aio_constructor_modifier(const str_hook *token);

#define AIO_CONSTRUCTOR_MODIFIER "typeinit"

/**
 * Keywords.
 */

#define AIO_IF_MODIFIER "if"

#define AIO_IN_MODIFIER "in"

#define AIO_CYCLE_MODIFIER "cycle"

#define AIO_RETURN_MODIFIER "out"

#define AIO_SWITCH_MODIFIER "when"

#define AIO_BREAK_MODIFIER "break"

#define AIO_CONTINUE_MODIFIER "next"

bool is_aio_if_modifier(const str_hook *token);

bool is_aio_in_modifier(const str_hook *token);

bool is_aio_cycle_modifier(const str_hook *token);

bool is_aio_return_modifier(const str_hook *token);

bool is_aio_switch_modifier(const str_hook *token);

bool is_aio_break_modifier(const str_hook *token);

bool is_aio_continue_modifier(const str_hook *token);

/**
 * Value keywords.
 */

#define AIO_TRUE_VALUE "true"

#define AIO_FALSE_VALUE "false"

#define AIO_NULL_VALUE "nil"

bool is_aio_true_modifier(const str_hook *hook);

bool is_aio_false_modifier(const str_hook *hook);

bool is_aio_null_modifier(const str_hook *hook);

/**
 * Check.
 */

bool is_successful_aio_name(const str_hook *token);

#endif //AIO_MODIFIERS_H