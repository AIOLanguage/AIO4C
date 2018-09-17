#ifndef AIO_INHERITABLE_H
#define AIO_INHERITABLE_H

#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

using namespace lib4aio;

typedef enum aio_inherited_type {
    AIO_CLOSE, AIO_OPEN, AIO_ABSTRACT
} aio_inherited_type;

template<class T>
class aio_inheritable {

public:

    aio_inheritable(array_list<T> *parents, aio_inherited_type inherited_type);

    ~aio_inheritable();

    const aio_inherited_type get_inherited_type() const;

    const array_list<T> *get_parents() const;

private:

    aio_inherited_type inherited_type;

    array_list<T> *parents;

};

#endif //AIO_INHERITABLE_H