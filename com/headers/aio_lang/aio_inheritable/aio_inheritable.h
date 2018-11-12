#ifndef AIO_INHERITABLE_H
#define AIO_INHERITABLE_H

namespace lib4aio {

    template<class T>
    class array_list;

    class str_hook;
}

using namespace lib4aio;

template<typename T>
struct aio_inheritable {

    explicit aio_inheritable();

    ~aio_inheritable();

    bool operator==(const aio_inheritable &rhs) const;

    bool operator!=(const aio_inheritable &rhs) const;

    array_list<T> *parents;

    array_list<str_hook> *parent_names;

    array_list<T> *children;

    enum {
        AIO_INHERITED_TYPE_UNDEFINED,
        AIO_INHERITED_TYPE_CLOSE,
        AIO_INHERITED_TYPE_OPEN,
        AIO_INHERITED_TYPE_ABSTRACT
    } inherited_type;

protected:

    virtual bool compare(const T *o1, const T *o2) = 0;
};

#endif //AIO_INHERITABLE_H