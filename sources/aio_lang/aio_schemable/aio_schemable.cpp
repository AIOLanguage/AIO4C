//lang:
#include <aio_lang/aio_schemable/aio_schemable.h>
//runtime:
#include <aio_runtime/aio_task/aio_task.h>

template<typename T>
aio_schemable<T>::aio_schemable()
{
    this->instructions = new array_list<aio_task<T>>();
}

template<typename T>
aio_schemable<T>::~aio_schemable()
{
    this->instructions->free_elements();
    delete this->instructions;
}

template<typename T>
array_list<aio_task<T>> *aio_schemable<T>::get_instructions()
{
    return this->instructions;
}