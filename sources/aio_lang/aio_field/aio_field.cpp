#include <aio_lang/aio_field/aio_field.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

aio_field::aio_field()
{}

aio_field::~aio_field()
{
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    delete this->name;
    delete this->type;
}