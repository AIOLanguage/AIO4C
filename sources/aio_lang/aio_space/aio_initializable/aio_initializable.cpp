//lang:
#include <aio_lang/aio_space/aio_initializable/aio_initializable.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>

aio_initializable::aio_initializable()
{}

aio_initializable::~aio_initializable()
{
    this->constructor_definition_list->free_elements();
    delete this->constructor_definition_list;
}