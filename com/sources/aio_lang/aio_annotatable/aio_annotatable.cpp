//lang:
#include <aio_lang/aio_annotatable/aio_annotatable.h>
#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>

aio_annotatable::aio_annotatable()
{
    this->marknames = new array_list<aio_class>(true);
 }

aio_annotatable::~aio_annotatable()
{
    delete this->marknames;
}