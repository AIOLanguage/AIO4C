#ifndef AIO_MODIFIERS_H
#define AIO_MODIFIERS_H

#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

using namespace lib4aio;

/**
 * Visibility modifiers.
 */

#define AIO_GLOBAL_MODIFIER "global"

#define AIO_INTERNAL_MODIFIER "internal"

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

#define AIO_IMPORT_MODIFIER "plg"

/**
 * Class modifiers.
 */

#define AIO_CLASS_MODIFIER "typ"

/**
 * Function  modifier.
 */

#define AIO_FUNCTION_MODIFIER "fun"

#define AIO_OVERRIDE_MODIFIER "override"

#define AIO_IF_MODIFIER "if"

#define AIO_IN_MODIFIER "in"

#define AIO_LOOP_MODIFIER "loo"

#define AIO_RETURN_MODIFIER "out"

#define AIO_SWITCH_MODIFIER "whe"

#define AIO_BREAK_MODIFIER "brk"

#define AIO_CONTINUE_MODIFIER "nxt"

bool is_aio_fun_modifier(str_hook *hook);

bool is_aio_if_modifier(str_hook *hook);

bool is_aio_in_modifier(str_hook *hook);

bool is_aio_loop_modifier(str_hook *hook);

bool is_aio_return_modifier(str_hook *hook);

bool is_aio_switch_modifier(str_hook *hook);

bool is_aio_break_modifier(str_hook *hook);

bool is_aio_continue_modifier(str_hook *hook);

/**
 * Value modifiers.
 */

#define AIO_TRUE_VALUE "true"

#define AIO_FALSE_VALUE "false"

#define AIO_NULL_VALUE "nil"

bool is_aio_true_modifier(const str_hook *hook);

bool is_aio_false_modifier(const str_hook *hook);

bool is_aio_null_modifier(const str_hook *hook);

/**
 * Declare functions.
 */

bool can_use_name(const str_hook *hook);

#endif //AIO_MODIFIERS_H