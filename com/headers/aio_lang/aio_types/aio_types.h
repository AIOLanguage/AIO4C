#ifndef AIO_TYPE_H
#define AIO_TYPE_H

/**
 * 연결.
 */

namespace lib4aio {

    class str_hook;
}

using namespace lib4aio;

/**
 * Built-in types.
 */

#define INTEGER "Int"

#define DOUBLE "Double"

#define STRING "String"

#define BOOLEAN "Boolean"

#define ANY "Any"

#define AUTO "_"

/**
 * Functions.
 */

bool is_aio_type_hooked(const str_hook *hook);

bool is_aio_any_type_hooked(const str_hook *hook);

bool is_aio_int_type_hooked(const str_hook *hook);

bool is_aio_double_type_hooked(const str_hook *hook);

bool is_aio_string_type_hooked(const str_hook *hook);

bool is_aio_boolean_type_hooked(const str_hook *hook);

bool is_aio_type_not_initialized(const str_hook *hook);

#endif //AIO_TYPE_H