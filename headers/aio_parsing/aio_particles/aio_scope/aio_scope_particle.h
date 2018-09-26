#ifndef AIO_SCOPE_PARTICLE_H
#define AIO_SCOPE_PARTICLE_H

#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

using namespace lib4aio;

template <typename T> class aio_scope_particle : public aio_particle<T> {

public:

    aio_scope_particle();

    ~aio_scope_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(T *space);
};

#endif //AIO_SCOPE_PARTICLE_H