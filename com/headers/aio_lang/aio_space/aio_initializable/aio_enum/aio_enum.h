#ifndef AIO_ENUM_H
#define AIO_ENUM_H

/**
 * 연결.
 */

//lang:
#include <aio_lang/aio_space/aio_initializable/aio_initializable.h>

using namespace lib4aio;

struct aio_enum : aio_initializable {

    explicit aio_enum();

    ~aio_enum();

    array_list<aio_field> *elements;
};

#endif //AIO_ENUM_H