#ifndef AIO_RESERVED_NAMES_CONTAINER_H
#define AIO_RESERVED_NAMES_CONTAINER_H

#define AIO_GLOBAL_MODIFIER "glo"

#define AIO_IMPORT_MODIFIER "plg"

#define AIO_CLASS_MODIFIER "obj"

#define AIO_INTERFACE_MODIFIER "wra"

#define AIO_PROTECTED_MODIFIER "pro"

#define AIO_PRIVATE_MODIFIER "pri"

#define AIO_FUNCTION_MODIFIER "fun"

#define AIO_FIELD_MODIFIER "fld"

#define AIO_MUTABLE_MODIFIER "mu"

#define AIO_IF_MODIFIER "if"

#define AIO_IN_MODIFIER "in"

#define AIO_LOOP_MODIFIER "loo"

#define AIO_RETURN_MODIFIER "out"

#define AIO_SWITCH_MODIFIER "whe"

#define AIO_BREAK_MODIFIER "brk"

#define AIO_TRUE_VALUE "tru"

#define AIO_FALSE_VALUE "fls"

#define AIO_NULL_VALUE "voi"

_Bool is_aio_mutable_modifier(const struct str_hook *hook);

_Bool is_aio_if_modifier(const struct str_hook *hook);

_Bool is_aio_loop_modifier(const struct str_hook *hook);

_Bool is_aio_null_value_string(const char *string_value);

_Bool can_use_name(const struct str_hook *hook);

#endif //AIO_RESERVED_NAMES_CONTAINER_H