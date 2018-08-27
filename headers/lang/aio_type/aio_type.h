#ifndef AIO_TYPE_H
#define AIO_TYPE_H

#define INTEGER "Int"

#define DOUBLE "Dou"

#define STRING "Str"

#define BOOLEAN "Boo"

#define VOID "Voi"

#define AIO_NOT_INIT_TYPE "###"

_Bool is_aio_type_hooked(const struct str_hook *hook);

_Bool is_aio_void_type_hooked(const struct str_hook *hook);

_Bool is_aio_type_initialized(const struct str_hook *hook);

#endif //AIO_TYPE_H