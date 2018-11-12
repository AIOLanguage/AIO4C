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
    return static_cast<const aio_initializable &>(*this)
           == static_cast<const aio_initializable &>(rhs)
           && static_cast<const aio_inheritable<aio_class> &>(*this)
              == static_cast<const aio_inheritable<aio_class> &>(rhs);
}

bool aio_class::operator!=(const aio_class &rhs) const
{
    return (*this == rhs);
}

bool aio_class::compare(const aio_class *c1, const aio_class *c2){
    return *c1 == *c2;
}


bool aio_class::compare_classes(const aio_class *c1, const aio_class *c2)
{
    return *c1 == *c2;
}