#ifndef AIO_DOMAIN_PARTICLE_H
#define AIO_DOMAIN_PARTICLE_H

#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

using namespace lib4aio;

class aio_build_script_space;

class aio_build_script_domain_particle : public aio_particle<aio_build_script_space> {

public:

    const aio_particle_signal handle_symbol(const char symbol);

    void illuminate(aio_build_script_space *space);

    void reset();

private:

    typedef enum aio_particle_mode {
        AIO_SCAN_ATTRIBUTE, AIO_SCAN_OPENING_BRACE, AIO_SCAN_TREE
    } aio_particle_mode;

};

#endif //AIO_DOMAIN_PARTICLE_H