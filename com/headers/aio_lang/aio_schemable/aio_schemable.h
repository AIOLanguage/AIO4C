#ifndef AIO_SCHEMABLE_H
#define AIO_SCHEMABLE_H

namespace lib4aio {

    template<typename T>
    class array_list;
}

class aio_task;

struct aio_field;

using namespace lib4aio;

struct aio_schemable {

    aio_schemable();

    virtual ~aio_schemable();

    array_list<aio_field> *fields;

    array_list<aio_task> *instructions;
};

#endif //AIO_SCHEMABLE_H