//lang:
#include <aio_lang/aio_inheritable/aio_inheritable.cpp>
#include <aio_lang/aio_invokable/aio_function/aio_function.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

aio_function::aio_function()
{}

aio_function::~aio_function()
{
    delete this->name;
}