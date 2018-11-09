//lang:
#include <aio_lang/aio_field/aio_field.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <aio_lang/aio_types/aio_types.h>

aio_field::aio_field()
{
    this->name = nullptr;
    this->type = new str_hook(AUTO);
}

aio_field::~aio_field()
{
    delete this->name;
    delete this->type;
}