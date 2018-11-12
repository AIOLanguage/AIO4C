#ifndef AIO_SCHEMABLE_H
#define AIO_SCHEMABLE_H

#include <aio_lang/aio_visible/aio_visible.h>

namespace lib4aio {

    template<typename T>
    class array_list;
}

class aio_task;

struct aio_field;

using namespace lib4aio;

struct aio_schemable : public aio_visible {

    array_list<aio_field> *fields;

    array_list<aio_task> *instructions;

    aio_schemable();

    virtual ~aio_schemable();

    bool operator==(const aio_schemable &rhs) const;

    bool operator!=(const aio_schemable &rhs) const;
};

#endif //AIO_SCHEMABLE_H