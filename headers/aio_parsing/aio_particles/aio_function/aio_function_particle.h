#ifndef AIO_FUNCTION_PARTICLE_H
#define AIO_FUNCTION_PARTICLE_H

#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    template<typename T>
    class array_list;
}

using namespace lib4aio;

class aio_runtime;

class aio_function;

template<typename T>
class aio_function_particle : public aio_particle<T> {

public:

    aio_function_particle(aio_runtime *runtime, array_list<aio_function> *function_list);

    ~aio_function_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(T *space);

};

#endif //AIO_FUNCTION_PARTICLE_H