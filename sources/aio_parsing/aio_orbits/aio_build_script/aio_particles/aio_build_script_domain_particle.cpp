#include <aio_parsing/aio_orbits/aio_build_script/aio_particles/aio_build_script_domain_particle.h>

const aio_particle_signal aio_build_script_domain_particle::handle_symbol(const char symbol)
{
    return aio_particle::handle_symbol(symbol);
}

void aio_build_script_domain_particle::illuminate(aio_build_script_space *space)
{
    aio_particle::illuminate(space);
}

void aio_build_script_domain_particle::reset()
{
    aio_particle::reset();
}