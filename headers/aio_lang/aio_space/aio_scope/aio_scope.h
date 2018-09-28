#ifndef AIO_SCOPE_H
#define AIO_SCOPE_H

/**
 * 연결.
 */

#include <aio_lang/aio_space/aio_space.h>

class aio_scope : public aio_space {

public:

    explicit aio_scope();

    ~aio_scope();

    str_hook *name;
};

#endif //AIO_SCOPE_H