#ifndef AIO_FIELD_H
#define AIO_FIELD_H

/**
 * 연결.
 */

//lang:
#include <aio_lang/aio_visible/aio_visible.h>
#include <ostream>

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

    /**
     * Boilerplate.
     */

    explicit aio_field();

    ~aio_field();

    bool operator==(const aio_field &rhs) const;

    bool operator!=(const aio_field &rhs) const;

    void log() const;

    static bool compare_fields(const aio_field *o1, const aio_field *o2);

    friend std::ostream &operator<<(std::ostream &os, const aio_field &field);
};

#endif //AIO_FIELD_H