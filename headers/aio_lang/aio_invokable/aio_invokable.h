#ifndef AIO_INVOKABLE_H
#define AIO_INVOKABLE_H

/**
 * 연결.
 */

#include <aio_lang/aio_annotatable/aio_annotatable.h>
#include <aio_lang/aio_schemable/aio_schemable.h>

namespace lib4aio {

    class str_hook;

}

using namespace lib4aio;

class aio_invokable : public aio_annotatable, public aio_schemable {

public:

    explicit aio_invokable();

    virtual ~aio_invokable();

    const unsigned get_arg_count() const;

    const array_list<str_hook> *get_output_types() const;

protected:

    unsigned arg_count;

    array_list<str_hook> *output_types;
};

#endif //AIO_INVOKABLE_H