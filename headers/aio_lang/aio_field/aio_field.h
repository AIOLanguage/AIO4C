#ifndef AIO_FIELD_H
#define AIO_FIELD_H

/**
 * 연결.
 */

#include <aio_lang/aio_visibility/aio_visibility.h>

namespace lib4aio {

    class str_hook;
}

using namespace lib4aio;

struct aio_field {

    explicit aio_field();

    ~aio_field();

    str_hook *name;

    str_hook *type;

    bool is_array;

    bool is_mutable;

    aio_visibility visibility_type;
};

#endif //AIO_FIELD_H