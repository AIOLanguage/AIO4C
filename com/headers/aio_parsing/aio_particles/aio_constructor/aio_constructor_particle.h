#ifndef AIO_CONSTRUCTOR_PARTICLE_H
#define AIO_CONSTRUCTOR_PARTICLE_H

#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    template<typename T>
    class array_list;
}

using namespace lib4aio;

struct aio_class;

struct aio_constructor;

class aio_constructor_particle : public aio_particle<aio_class> {

public:

    aio_constructor_particle();

    ~aio_constructor_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(aio_class *class_ptr);
};

#endif //AIO_CONSTRUCTOR_PARTICLE_H