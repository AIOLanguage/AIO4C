#ifndef AIO_CONSTRUCTOR_H
#define AIO_CONSTRUCTOR_H

/**
 * 연결.
 */

#include <aio_lang/aio_invokable/aio_invokable.h>
#include <aio_lang/aio_inheritable/aio_inheritable.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

class aio_constructor : aio_invokable, aio_inheritable<aio_constructor> {

    aio_constructor();

    ~aio_constructor();
};

#endif //AIO_CONSTRUCTOR_H