//lang:
#include <aio_lang/aio_invokable/aio_constructor/aio_constructor.h>
//parsing:
#include <aio_parsing/aio_particles/aio_constructor/aio_constructor_particle.h>

template<typename T>
aio_constructor_particle<T>::aio_constructor_particle(
        aio_runtime *runtime_ptr,
        array_list<aio_constructor> *constructor_list_ptr
)
{

}

template<typename T>
aio_constructor_particle<T>::~aio_constructor_particle()
{

}

template<typename T>
const aio_particle_signal aio_constructor_particle<T>::handle_symbol(const unsigned position)
{
    return AIO_PARTICLE_SIGNAL_DETECTED;
}

template<typename T>
unsigned aio_constructor_particle<T>::illuminate(T *container)
{
    return 0;
}
