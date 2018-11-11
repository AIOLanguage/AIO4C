#ifndef AIO_FIELD_H
#define AIO_FIELD_H

/**
 * 연결.
 */

//lang:
#include <aio_lang/aio_visibility/aio_visibility.h>
#include <ostream>

namespace lib4aio {

    class str_hook;
}

using namespace lib4aio;

using namespace std;

struct aio_field {

    explicit aio_field();

    ~aio_field();

    str_hook *name;

    str_hook *type;

    bool is_array;

    bool is_const;

    bool is_static;

    aio_visibility visibility_type;

    bool equals(const aio_field *other) const;
};

void log_aio_field(const aio_field * field);

#endif //AIO_FIELD_H