#ifndef AIO_EXPRESSION_PARTICLE_H
#define AIO_EXPRESSION_PARTICLE_H

#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

using namespace lib4aio;

class aio_build_script_space;

class aio_build_script_config_particle : public aio_particle<aio_build_script_space> {

public:

    const aio_particle_signal handle_symbol(const char symbol);

    void illuminate(aio_build_script_space *space);

    void reset();

private:

    typedef enum aio_particle_mode {
        AIO_SCAN_ATTRIBUTE, AIO_SCAN_EQUAL_SIGN, AIO_SCAN_VALUE
    } aio_particle_mode;

};

#endif //AIO_EXPRESSION_PARTICLE_H