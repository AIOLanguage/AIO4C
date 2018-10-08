#ifndef AIO_FUNCTION_H
#define AIO_FUNCTION_H

/**
 * 연결.
 */

//lang:
#include <aio_lang/aio_invokable/aio_invokable.h>
#include <aio_lang/aio_inheritable/aio_inheritable.h>

struct aio_function : public aio_invokable, public aio_inheritable<aio_function> {

    explicit aio_function();

    ~aio_function();

    str_hook *name;
};

#endif //AIO_FUNCTION_H