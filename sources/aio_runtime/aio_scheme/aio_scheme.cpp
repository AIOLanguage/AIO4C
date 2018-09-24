#include <aio_runtime/aio_scheme/aio_scheme.h>

aio_scheme::aio_scheme()
{}

aio_scheme::~aio_scheme()
{}

const aio_scheme *aio_scheme::get_parent() const
{
    return this->parent;
}

const array_list<aio_field> *aio_scheme::get_field_definitions() const
{
    return this->field_definitions;
}

const array_list<aio_instruction> *aio_scheme::get_instructions() const
{
    return this->instructions;
}