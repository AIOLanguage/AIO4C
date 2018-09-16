#ifndef AIO_ANNOTATABLE_H
#define AIO_ANNOTATABLE_H

#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>

class aio_annotatable {

private:

    array_list<aio_class> *annotation_definition_list;

public:

    aio_annotatable(array_list<aio_class> *annotation_definition_list);

    ~aio_annotatable();

    const array_list<aio_class> *get_annotation_definition_list() const;

};

#endif //AIO_ANNOTATABLE_H