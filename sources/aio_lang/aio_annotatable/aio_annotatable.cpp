#include <aio_lang/aio_annotatable/aio_annotatable.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>

aio_annotatable::aio_annotatable()
{
    this->annotation_definition_list = new array_list<aio_class>();
    this->annotation_names = new array_list<str_hook>();
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
