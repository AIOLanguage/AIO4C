#include <aio_runtime/aio_ray/aio_ray.h>

template<typename T>
aio_ray<T>::aio_ray()
{

}

template<typename T>
aio_ray<T>::~aio_ray()
{

}

template<typename T>
void aio_ray<T>::complete()
{

}

template<typename T>
aio_ray<T> *aio_ray<T>::perform(const T *container)
{
    return nullptr;
}

template<typename T>
array_list<aio_variable> *aio_ray<T>::get_variables() const
{
    return nullptr;
}

template<typename T>
const aio_ray_state aio_ray<T>::get_state() const
{
    return *this->state;
}

template<typename T>
void aio_ray<T>::set_ray_state(aio_ray_state ray_state)
{
    *this->state = ray_state;
}