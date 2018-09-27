#ifndef AIO_INHERITABLE_H
#define AIO_INHERITABLE_H

namespace lib4aio {

    template<class T>
    class array_list;

    class str_hook;
}

using namespace lib4aio;

typedef enum aio_inherited_type {
    AIO_INHERITED_TYPE_UNDEFINED,
    AIO_INHERITED_TYPE_CLOSE,
    AIO_INHERITED_TYPE_OPEN,
    AIO_INHERITED_TYPE_ABSTRACT
} aio_inherited_type;

template<class T>
class aio_inheritable {

public:

    explicit aio_inheritable();

    ~aio_inheritable();

    aio_inherited_type inherited_type;

    array_list<T> *parents;

    array_list<str_hook> *parent_names;
};

#endif //AIO_INHERITABLE_H