//lang:
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_space/aio_initializable/aio_enum/aio_enum.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

using namespace lib4aio;

aio_enum::aio_enum()
{
    this->elements = new array_list<aio_field>(true);
}

aio_enum::~aio_enum()
{
    delete this->elements;
}

bool aio_enum::operator==(const aio_enum &rhs) const
{
    return static_cast<const aio_initializable &>(*this)
           == static_cast<const aio_initializable &>(rhs)
           && this->elements->equals(rhs.elements, aio_field::compare);
}

bool aio_enum::operator!=(const aio_enum &rhs) const
{
    return !(rhs == *this);
}

static bool compare_enums(const aio_enum *o1, const aio_enum *o2)
{
    return *o1 == *o2;
}