#ifndef AIO_INVOKABLE_H
#define AIO_INVOKABLE_H

/**
 * 연결.
 */

//lang:
#include <aio_lang/aio_schemable/aio_schemable.h>
#include <aio_lang/aio_annotatable/aio_annotatable.h>

namespace lib4aio {

    class str_hook;
}

using namespace lib4aio;

struct aio_invokable : public aio_annotatable, public aio_schemable {

    explicit aio_invokable();

    virtual ~aio_invokable();

    bool operator==(const aio_invokable &rhs) const;

    bool operator!=(const aio_invokable &rhs) const;

    unsigned arg_count;

    str_hook *output_type;

    bool is_array_output;
};

#endif //AIO_INVOKABLE_H