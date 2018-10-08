#ifndef AIO_CLASS_H
#define AIO_CLASS_H

/**
 * 연결.
 */

//lang:
#include <aio_lang/aio_inheritable/aio_inheritable.h>
#include <aio_lang/aio_space/aio_initializable/aio_initializable.h>

using namespace lib4aio;

struct aio_class : public aio_initializable, public aio_inheritable<aio_class> {

    explicit aio_class();

    ~aio_class();
};

#endif //AIO_CLASS_H