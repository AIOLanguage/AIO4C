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
    if (!this->parents->equals(rhs.parents, [this](const T *o1, const T *o2) { return this->compare(o1, o2); })) {
        return false;
    }
    printf("PARENTS IS OK\n");
    if (!this->parent_names->equals(rhs.parent_names, str_hook::compare_hooks)) {
        return false;
    }
    printf("NAMES IS OK\n");
    if (!this->children->equals(rhs.children, [this](const T *o1, const T *o2) { return this->compare(o1, o2); })) {
        return false;
    }
    printf("CHILDREN ARE OK\n");
    if (this->inherited_type != rhs.inherited_type) {
        return false;
    }
    printf("INHERITANCE IS OK\n");
    return true;
}

template<typename T>
bool aio_inheritable<T>::operator!=(const aio_inheritable &rhs) const
{
    return !(rhs == *this);
}