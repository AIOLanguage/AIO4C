//runtime:
#include <aio_runtime/aio_task/aio_task.cpp>
#include <aio_runtime/aio_task/aio_assign/aio_assign_task.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

template<typename T>
aio_assign_task<T>::aio_assign_task()
{}

template<typename T>
aio_assign_task<T>::~aio_assign_task()
{
    delete this->name;
    delete this->value;
}

template<typename T>
void aio_assign_task<T>::perform(aio_ray<T> *ray)
{}

template<typename T>
void aio_assign_task<T>::set_name(str_hook *name)
{
    this->name = name;
}

template<typename T>
void aio_assign_task<T>::set_value(char *value)
{
    this->value = value;
}

template<typename T>
const str_hook *aio_assign_task<T>::get_name()
{
    return this->name;
}

template<typename T>
const char *aio_assign_task<T>::get_value()
{
    return this->value;
}