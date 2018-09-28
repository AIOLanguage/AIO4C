#ifndef AIO_CONSTRUCTOR_PARTICLE_H
#define AIO_CONSTRUCTOR_PARTICLE_H

#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    template<typename T>
    class array_list;
}

using namespace lib4aio;

class aio_runtime;

class aio_constructor;

template<typename T>
class aio_constructor_particle : public aio_particle<T> {

public:

    aio_constructor_particle(aio_runtime *runtime_ptr, array_list<aio_constructor> *constructor_list_ptr);

    ~aio_constructor_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(T *container);
};

#endif //AIO_CONSTRUCTOR_PARTICLE_H