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

const str_hook *aio_field::get_name() const
{
    return this->name;
}

const str_hook *aio_field::get_type() const
{
    return this->type;
}

const bool aio_field::is_array_type() const
{

    return this->is_array;
}

const bool aio_field::is_mutable_type() const
{
    return this->is_mutable;
}

const aio_visibility aio_field::get_visibility_type() const
{
    return this->visibility_type;
}