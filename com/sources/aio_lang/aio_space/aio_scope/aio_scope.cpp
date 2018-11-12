#include <aio_lang/aio_space/aio_scope/aio_scope.h>

aio_scope::aio_scope()
{}

aio_scope::~aio_scope()
{}

bool aio_scope::operator==(const aio_scope &rhs) const
{
    return static_cast<const aio_space &>(*this) == static_cast<const aio_space &>(rhs)
           && this->name == rhs.name;
}

bool aio_scope::operator!=(const aio_scope &rhs) const
{
    return !(rhs == *this);
}

static bool compare_scopes(const aio_scope *o1, const aio_scope *o2)
{
    return *o1 == *o2;
}