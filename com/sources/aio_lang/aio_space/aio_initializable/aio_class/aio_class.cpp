//lang:
#include <aio_lang/aio_inheritable/aio_inheritable.cpp>
#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

aio_class::aio_class()
{}

aio_class::~aio_class()
{}

bool aio_class::operator==(const aio_class &rhs) const
{
    printf("START\n");
    if (static_cast<const aio_initializable &>(*this)
        != static_cast<const aio_initializable &>(rhs)) {
        return false;
    }
    printf("INIT IS OKAY\n");
    if (static_cast<const aio_inheritable<aio_class> &>(*this)
        != static_cast<const aio_inheritable<aio_class> &>(rhs)) {
        return false;
    }
    printf("INHERIT IS OKAY\n");
    return true;
}

bool aio_class::operator!=(const aio_class &rhs) const
{
    return (*this == rhs);
}

bool aio_class::compare(const aio_class *c1, const aio_class *c2) const
{
    return *c1 == *c2;
}


bool aio_class::compare_classes(const aio_class *c1, const aio_class *c2)
{
    return *c1 == *c2;
}

ostream &operator<<(ostream &os, const aio_class &aClass)
{
    os << static_cast<const aio_initializable &>(aClass) << ' ';
    return os;
}
