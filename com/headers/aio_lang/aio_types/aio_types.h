#ifndef AIO_TYPE_H
#define AIO_TYPE_H

/**
 * 연결.
 */

#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

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
 * Config types.
 */

#define AIOMAIN_TYPE "AIOMain"

#define AIOPROCESSOR_TYPE "AIOProcessor"

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