#ifndef AIO_FIELD_H
#define AIO_FIELD_H

/**
 * 연결.
 */

//lang:
#include <aio_lang/aio_visible/aio_visible.h>

namespace lib4aio {

    class str_hook;
}

using namespace lib4aio;

struct aio_field : public aio_visible {

    str_hook *name;

    str_hook *type;

    bool is_array;

    bool is_const;

    bool is_static;

    explicit aio_field();

    ~aio_field();

    bool operator==(const aio_field &rhs) const;

    bool operator!=(const aio_field &rhs) const;

    void log_aio_field() const;

    static bool compare(const aio_field *o1, const aio_field *o2);
};

#endif //AIO_FIELD_H