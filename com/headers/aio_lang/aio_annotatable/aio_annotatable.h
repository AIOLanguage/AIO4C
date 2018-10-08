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

    array_list<aio_class> *marknames;
};

#endif //AIO_ANNOTATABLE_H