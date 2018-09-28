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

/**
 * Attribute modifier.
 */

#define AIO_OPEN_MODIFIER "open"

#define AIO_ABSTRACT_MODIFIER "abstract"

/**
 * Import modifier.
 */

#define AIO_IMPORT_MODIFIER "addition"

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

bool is_aio_fun_modifier(str_hook *hook);

/**
 * Constructor modifier.
 */

#define AIO_CONSTRUCTOR_MODIFIER "typeinit"

/**
 * Keywords.
 */

#define AIO_IF_MODIFIER "if"

#define AIO_IN_MODIFIER "in"

#define AIO_LOOP_MODIFIER "cycle"

#define AIO_RETURN_MODIFIER "out"

#define AIO_SWITCH_MODIFIER "when"

#define AIO_BREAK_MODIFIER "break"

#define AIO_CONTINUE_MODIFIER "next"

bool is_aio_if_modifier(str_hook *hook);

bool is_aio_in_modifier(str_hook *hook);

bool is_aio_loop_modifier(str_hook *hook);

bool is_aio_return_modifier(str_hook *hook);

bool is_aio_switch_modifier(str_hook *hook);

bool is_aio_break_modifier(str_hook *hook);

bool is_aio_continue_modifier(str_hook *hook);

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

bool is_successful_aio_name(const str_hook *hook);

#endif //AIO_MODIFIERS_H