//lang:
#include <aio_lang/aio_inheritable/aio_inheritable.h>
//lib4aio:
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>

template<class T>
aio_inheritable<T>::aio_inheritable()
{
    this->parents = new array_list<T>(false);
}

template<class T>
aio_inheritable<T>::~aio_inheritable()
{
    delete this->parents;
}