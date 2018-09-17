#ifndef AIO_ANNOTATABLE_H
#define AIO_ANNOTATABLE_H

#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

using namespace lib4aio;

class aio_class;

class aio_annotatable {

public:

    explicit aio_annotatable(array_list<aio_class> *annotation_definition_list);

    virtual ~aio_annotatable();

    const array_list<aio_class> *get_annotation_definition_list() const;

private:

    array_list<aio_class> *annotation_definition_list;

};

#endif //AIO_ANNOTATABLE_H