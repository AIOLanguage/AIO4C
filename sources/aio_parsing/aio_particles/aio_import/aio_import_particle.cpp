#include <aio_parsing/aio_particles/aio_import/aio_import_particle.h>

template<typename T>
aio_import_particle<T>::aio_import_particle(array_list<aio_file> *file_list)
{

}

template<typename T>
aio_import_particle<T>::~aio_import_particle()
{

}

template<typename T>
const aio_particle_signal aio_import_particle<T>::handle_symbol(const unsigned position)
{
    return AIO_PARTICLE_SIGNAL_DETECTED;
}

template<typename T>
unsigned aio_import_particle<T>::illuminate(T *space)
{
    return 0;
}