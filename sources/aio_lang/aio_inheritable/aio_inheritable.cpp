#include <aio_lang/aio_inheritable/aio_inheritable.h>

template<class T>
aio_inheritable<T>::aio_inheritable(array_list<T> *parents, aio_inherited_type inherited_type)
{
    this->parents = parents;
    this->inherited_type = inherited_type;
}

template<class T>
aio_inheritable<T>::~aio_inheritable()
{
    delete this->parents;
}

template<class T>
const aio_inherited_type aio_inheritable<T>::get_inherited_type() const
{
    return this->inherited_type;
}

template<class T>
const array_list<T> *aio_inheritable<T>::get_parents() const
{
    return this->parents;
}