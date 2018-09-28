#ifndef AIO_SCHEMABLE_H
#define AIO_SCHEMABLE_H

namespace lib4aio {

    template<typename T>
    class array_list;
}

using namespace lib4aio;

template<typename T>
class aio_task;

template<typename T>
class aio_schemable {

public:

    aio_schemable();

    virtual ~aio_schemable();

    array_list<aio_task<T>> *get_instructions();

private:

    array_list<aio_task<T>> *instructions;
};

#endif //AIO_SCHEMABLE_H