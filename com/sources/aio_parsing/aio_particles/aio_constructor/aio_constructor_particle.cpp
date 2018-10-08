//lang:
#include <aio_lang/aio_invokable/aio_constructor/aio_constructor.h>
//parsing:
#include <aio_parsing/aio_particles/aio_constructor/aio_constructor_particle.h>
//lib4aio:
#include <lib4aio_cpp_sources/aio_orbit/aio_particle/aio_particle.cpp>

aio_constructor_particle::aio_constructor_particle()
{}

aio_constructor_particle::~aio_constructor_particle()
{}

const aio_particle_signal aio_constructor_particle::handle_symbol(const unsigned position)
{
    return AIO_PARTICLE_SIGNAL_DETECTED;
}

unsigned aio_constructor_particle::illuminate(aio_class *container)
{
    return 0;
}