#ifndef AIO_ENUM_H
#define AIO_ENUM_H

/**
 * 연결.
 */

#include <aio_lang/aio_space/aio_initializable/aio_initializable.h>

using namespace lib4aio;

class aio_enum : aio_initializable {

public:

    explicit aio_enum();

    ~aio_enum();

    const array_list<aio_field> *get_values() const;

private:

    array_list<aio_field> *elements;
};

#endif //AIO_ENUM_H