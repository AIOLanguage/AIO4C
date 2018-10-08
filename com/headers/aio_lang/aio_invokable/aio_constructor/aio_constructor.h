#ifndef AIO_CONSTRUCTOR_H
#define AIO_CONSTRUCTOR_H

/**
 * 연결.
 */

//lang:
#include <aio_lang/aio_invokable/aio_invokable.h>
#include <aio_lang/aio_inheritable/aio_inheritable.h>

struct aio_constructor : public aio_invokable, public aio_inheritable<aio_constructor> {

    aio_constructor();

    ~aio_constructor();
};

#endif //AIO_CONSTRUCTOR_H