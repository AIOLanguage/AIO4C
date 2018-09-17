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

class aio_field {

public:

    explicit aio_field(
            str_hook *name,
            str_hook *type,
            const bool is_array,
            const bool is_mutable,
            const aio_visibility visibility_type
    );

    ~aio_field();

    const str_hook *get_name() const;

    const str_hook *get_type() const;

    const bool is_array_type() const;

    const bool is_mutable_type() const;

    const aio_visibility get_visibility_type() const;

private:

    str_hook *name;

    str_hook *type;

    bool is_array;

    bool is_mutable;

    aio_visibility visibility_type;

};

#endif //AIO_FIELD_H