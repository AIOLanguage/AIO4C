#ifndef LIB4AIO_CPP_AIO_MONITOR_PARTICLE_H
#define LIB4AIO_CPP_AIO_MONITOR_PARTICLE_H

#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    template <class T> class aio_monitor_particle : public aio_particle<T> {


        aio_monitor_particle();

        ~aio_monitor_particle();

        const aio_particle_signal handle_symbol(const unsigned position);

        unsigned illuminate(T *space);

        void reset();
    };
}


#endif //LIB4AIO_CPP_AIO_MONITOR_PARTICLE_H