#ifndef AIO_CLASS_PARTICLE_H
#define AIO_CLASS_PARTICLE_H

/**
 * 연결.
 */

#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

class aio_space;

using namespace lib4aio;

template<typename T>
class aio_class_particle : public aio_particle<T> {

public:

    explicit aio_class_particle();

    ~aio_class_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(T *space);

};

template<typename T>
const aio_particle_signal aio_class_particle<T>::handle_symbol(const unsigned position)
{
    return AIO_PARTICLE_SIGNAL_DETECTED;
}

template<typename T>
unsigned aio_class_particle<T>::illuminate(T *space)
{
    return 0;
}

template<typename T>
aio_class_particle<T>::aio_class_particle()
{

}

template<typename T>
aio_class_particle<T>::~aio_class_particle()
{

}

#endif //AIO_CLASS_PARTICLE_H