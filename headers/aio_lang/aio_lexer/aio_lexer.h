#ifndef AIO_LEXER_H
#define AIO_LEXER_H

#include <lib4aio_cpp_headers/utils/str_hook/str_hook/str_hook.h>

using namespace lib4aio;

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

#define AIO_CONTINUE_MODIFIER "cnt"

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

#define AIO_TRUE_VALUE "tru"

#define AIO_FALSE_VALUE "fls"

#define AIO_NULL_VALUE "nul"

bool is_aio_true_modifier(const str_hook *hook);

bool is_aio_false_modifier(const str_hook *hook);

bool is_aio_null_modifier(const str_hook *hook);

/**
 * Declare functions.
 */

bool can_use_name(const str_hook *hook);

#endif //AIO_LEXER_H