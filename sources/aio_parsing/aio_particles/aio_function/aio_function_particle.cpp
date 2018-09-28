#include <aio_parsing/aio_particles/aio_function/aio_function_particle.h>

template<typename T>
aio_function_particle<T>::aio_function_particle(aio_runtime *runtime, array_list<aio_function> *function_list)
{

}

template<typename T>
aio_function_particle<T>::~aio_function_particle()
{

}

template<typename T>
const aio_particle_signal aio_function_particle<T>::handle_symbol(const unsigned position)
{
    return AIO_PARTICLE_SIGNAL_DETECTED;
}

template<typename T>
unsigned aio_function_particle<T>::illuminate(T *space)
{
    return 0;
}