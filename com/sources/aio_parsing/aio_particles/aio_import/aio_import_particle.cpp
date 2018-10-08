//parsing:
#include <aio_parsing/aio_particles/aio_import/aio_import_particle.h>
//lib4aio:
#include <lib4aio_cpp_sources/aio_orbit/aio_particle/aio_particle.cpp>

aio_import_particle::aio_import_particle()
{}

aio_import_particle::~aio_import_particle()
{}

const aio_particle_signal aio_import_particle::handle_symbol(const unsigned position)
{
    return AIO_PARTICLE_SIGNAL_DETECTED;
}

unsigned aio_import_particle::illuminate(aio_file *file)
{
    return 0;
}