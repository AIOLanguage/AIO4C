#include <aio_lang/aio_annotatable/aio_annotatable.h>

aio_annotatable::aio_annotatable(array_list <aio_class> *annotation_definition_list)
{
    this->annotation_definition_list = annotation_definition_list;
}

aio_annotatable::~aio_annotatable()
{
    this->annotation_definition_list->free_elements();
    delete this->annotation_definition_list;
}

const array_list<aio_class> *aio_annotatable::get_annotation_definition_list() const
{
    return this->annotation_definition_list;
}
