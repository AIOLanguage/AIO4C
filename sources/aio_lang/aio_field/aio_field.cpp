#include <aio_lang/aio_field/aio_field.h>

aio_field::aio_field(
        str_hook *name,
        str_hook *type,
        const bool is_array,
        const bool is_mutable,
        const aio_visibility visibility_type
)
{
    this->name = name;
    this->type = type;
    this->is_array = is_array;
    this->is_mutable = is_mutable;
    this->visibility_type = visibility_type;
}

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
