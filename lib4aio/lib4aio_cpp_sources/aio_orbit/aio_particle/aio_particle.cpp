#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    template<class S>
    aio_particle<S>::aio_particle()
    {}

    template<class S>
    aio_particle<S>::~aio_particle()
    {}

    template<class S>
    void aio_particle<S>::rotate_around(aio_orbit<S> *orbit)
    {
        this->parent_orbit = orbit;
    }
}