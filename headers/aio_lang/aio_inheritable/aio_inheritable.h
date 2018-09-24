#ifndef AIO_INHERITABLE_H
#define AIO_INHERITABLE_H

namespace lib4aio {

    template <class T> class array_list;
}

using namespace lib4aio;

typedef enum aio_inherited_type {
    AIO_CLOSE, AIO_OPEN, AIO_ABSTRACT
} aio_inherited_type;

template<class T>
class aio_inheritable {

public:

    explicit aio_inheritable();

    ~aio_inheritable();

    const aio_inherited_type get_inherited_type() const;

    const array_list<T> *get_parents() const;

protected:

    aio_inherited_type inherited_type;

    array_list<T> *parents;
};

#endif //AIO_INHERITABLE_H