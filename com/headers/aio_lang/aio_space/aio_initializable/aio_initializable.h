#ifndef AIO_INITIALIZABLE_H
#define AIO_INITIALIZABLE_H

/**
 * 연결.
 */

#include <aio_lang/aio_space/aio_space.h>
#include <ostream>

namespace lib4aio {

    class str_hook;
}

struct aio_constructor;

struct aio_initializable : public aio_space {

    explicit aio_initializable();

    virtual ~aio_initializable();

    friend std::ostream &operator<<(std::ostream &os, const aio_initializable &initializable);

    str_hook *name;

    array_list<aio_constructor> *constructors;
};

#endif //AIO_INITIALIZABLE_H