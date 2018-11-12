#ifndef AIO_ANNOTATABLE_H
#define AIO_ANNOTATABLE_H

namespace lib4aio {

    template<class T>
    class array_list;

    class str_hook;
}

struct aio_class;

using namespace lib4aio;

struct aio_annotatable {

    explicit aio_annotatable();

    virtual ~aio_annotatable();

    bool operator==(const aio_annotatable &rhs) const;

    bool operator!=(const aio_annotatable &rhs) const;

    array_list<aio_class> *annotations;

    array_list<str_hook> *annotation_names;
};

#endif //AIO_ANNOTATABLE_H