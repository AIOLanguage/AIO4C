//lang:
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_schemable/aio_schemable.h>
//runtime:
#include <aio_runtime/aio_task/aio_task.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>

aio_schemable::aio_schemable()
{
    this->instructions = new array_list<aio_task>(true);
    this->fields = new array_list<aio_field>(true);
}

aio_schemable::~aio_schemable()
{
    delete this->instructions;
    delete this->fields;
}

bool aio_schemable::operator==(const aio_schemable &rhs) const
{
    return static_cast<const aio_visible &>(*this) == static_cast<const aio_visible &>(rhs)
           && this->fields->equals(rhs.fields, aio_field::compare)
           && this->instructions->equals(rhs.instructions, aio_task::compare);
}

bool aio_schemable::operator!=(const aio_schemable &rhs) const
{
    return !(rhs == *this);
}