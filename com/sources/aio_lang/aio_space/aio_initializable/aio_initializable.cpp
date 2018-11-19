//lang:
#include <aio_lang/aio_invokable/aio_constructor/aio_constructor.h>
#include <aio_lang/aio_space/aio_initializable/aio_initializable.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

aio_initializable::aio_initializable()
{
    this->constructors = new array_list<aio_constructor>(true);
}

aio_initializable::~aio_initializable()
{
    delete this->constructors;
}

bool aio_initializable::operator==(const aio_initializable &rhs) const {
    return this->name->equals_string(rhs.name);
}

bool aio_initializable::operator!=(const aio_initializable &rhs) const {
    return !(*this == rhs);
}

ostream &operator<<(ostream &os, const aio_initializable &initializable)
{
    os << static_cast<const aio_space &>(initializable) << " name: " << initializable.name;
    return os;
}
