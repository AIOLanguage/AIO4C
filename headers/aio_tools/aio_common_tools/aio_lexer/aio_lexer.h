#ifndef AIO_LEXER_H
#define AIO_LEXER_H

/**
 * Visibility modifiers.
 */

#define AIO_GLOBAL_MODIFIER "glo"

#define AIO_PROTECTED_MODIFIER "pro"

#define AIO_PRIVATE_MODIFIER "pri"

/**
 * Import modifier.
 */

#define AIO_IMPORT_MODIFIER "plg"

/**
 * Class modifiers.
 */

#define AIO_CLASS_MODIFIER "obj"

#define AIO_INTERFACE_MODIFIER "wra"

/**
 * Field modifier.
 */

#define AIO_FIELD_MODIFIER "fld"

/**
 * Mutable modifier.
 */

#define AIO_MUTABLE_MODIFIER "mu"

/**
 * Function  modifier.
 */

#define AIO_FUNCTION_MODIFIER "fun"

#define AIO_IF_MODIFIER "if"

#define AIO_IN_MODIFIER "in"

#define AIO_LOOP_MODIFIER "loo"

#define AIO_RETURN_MODIFIER "out"

#define AIO_SWITCH_MODIFIER "whe"

#define AIO_BREAK_MODIFIER "brk"

/**
 * Value modifiers.
 */

#define AIO_TRUE_VALUE "tru"

#define AIO_FALSE_VALUE "fls"

#define AIO_NULL_VALUE "voi"

/**
 * Declare functions.
 */

_Bool is_aio_mutable_modifier(const struct str_hook *hook);

_Bool is_aio_if_modifier(const struct str_hook *hook);

_Bool is_aio_loop_modifier(const struct str_hook *hook);

_Bool is_aio_null_value_string(const char *string_value);

_Bool can_use_name(const struct str_hook *hook);

#endif //AIO_LEXER_H