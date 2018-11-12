//lang:
#include <aio_lang/aio_inheritable/aio_inheritable.h>
//lib4aio:
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

template<class T>
aio_inheritable<T>::aio_inheritable()
{
    this->parents = new array_list<T>(false);
    this->children = new array_list<T>(true);
    this->parent_names = new array_list<str_hook>(true);
    this->inherited_type = AIO_INHERITED_TYPE_UNDEFINED;
}

template<class T>
aio_inheritable<T>::~aio_inheritable()
{
    delete this->parents;
}

template<typename T>
bool aio_inheritable<T>::operator==(const aio_inheritable &rhs) const
{
    return
//    this->parents->equals(rhs.parents, this->compare)
            this->parent_names->equals(rhs.parent_names, str_hook::compare)
//           && this->children->equals(rhs.children, this->compare)
           && this->inherited_type == rhs.inherited_type;
}

template<typename T>
bool aio_inheritable<T>::operator!=(const aio_inheritable &rhs) const
{
    return !(rhs == *this);
}