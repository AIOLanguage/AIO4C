#ifndef AIO_ENUM_H
#define AIO_ENUM_H

/**
 * 연결.
 */

//lang:
#include <aio_lang/aio_space/aio_initializable/aio_initializable.h>

using namespace lib4aio;

struct aio_enum : aio_initializable {

    array_list<aio_field> *elements;

    explicit aio_enum();

    ~aio_enum();

    bool operator==(const aio_enum &rhs) const;

    bool operator!=(const aio_enum &rhs) const;

    static bool compare_enums(const aio_enum *o1, const aio_enum *o2);
};

#endif //AIO_ENUM_H