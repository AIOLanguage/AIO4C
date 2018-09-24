#include <aio_lang/aio_schemable/aio_schemable.h>

aio_schemable::aio_schemable()
{}

aio_schemable::~aio_schemable()
{}

aio_scheme *aio_schemable::get_scheme() const
{
    return this->scheme;
}