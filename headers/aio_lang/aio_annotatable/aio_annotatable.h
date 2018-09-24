#ifndef AIO_ANNOTATABLE_H
#define AIO_ANNOTATABLE_H

namespace lib4aio {

    template<class T>
    class array_list;
}

class aio_class;

using namespace lib4aio;

class aio_annotatable {

public:

    explicit aio_annotatable();

    virtual ~aio_annotatable();

    virtual const array_list<aio_class> *get_annotation_definition_list() const;

protected:

    array_list<aio_class> *annotation_definition_list;
};

#endif //AIO_ANNOTATABLE_H