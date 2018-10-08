//lang:
#include <aio_lang/aio_field/aio_field.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

aio_field::aio_field()
{
    this->name = nullptr;
    this->type = nullptr;
}

aio_field::~aio_field()
{
    delete this->name;
    delete this->type;
}