//lang:
#include <aio_lang/aio_invokable/aio_invokable.h>
//#include <aio_lang/aio_schemable/aio_schemable.cpp>
//lib4aio:
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <aio_lang/aio_types/aio_types.h>

using namespace lib4aio;

aio_invokable::aio_invokable()
{

    this->output_type = nullptr;
    this->is_array_output = false;
    this->arg_count = 0;
}

aio_invokable::~aio_invokable()
{
    delete this->output_type;
}

bool aio_invokable::operator==(const aio_invokable &rhs) const
{
    return static_cast<const aio_annotatable &>(*this) == static_cast<const aio_annotatable &>(rhs)
           && static_cast<const aio_schemable &>(*this) == static_cast<const aio_schemable &>(rhs)
           && this->arg_count == rhs.arg_count
           && *this->output_type == *rhs.output_type
           && this->is_array_output == rhs.is_array_output;
}

bool aio_invokable::operator!=(const aio_invokable &rhs) const
{
    return !(rhs == *this);
}