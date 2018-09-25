#include <aio_lang/aio_invokable/aio_function/aio_function.h>
#include <aio_lang/aio_inheritable/aio_inheritable.cpp>

aio_function::aio_function()
{}

aio_function::~aio_function()
{
    delete this->name;
}

const str_hook *aio_function::get_name() const
{
    return this->name;
}