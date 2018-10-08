//lang:
#include <aio_lang/aio_space/aio_initializable/aio_enum/aio_enum.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

using namespace lib4aio;

aio_enum::aio_enum()
{}

aio_enum::~aio_enum()
{
    this->elements->free_elements();
    delete this->elements;
}