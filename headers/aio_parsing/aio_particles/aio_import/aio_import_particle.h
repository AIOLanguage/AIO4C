#ifndef AIO_IMPORT_PARTICLE_H
#define AIO_IMPORT_PARTICLE_H

#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    template<typename T>
    class array_list;
}

class aio_file;

using namespace lib4aio;

template<typename T>
class aio_import_particle : public aio_particle<T> {

public:

    explicit aio_import_particle(array_list<aio_file> *file_list);

    ~aio_import_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(T *space);
};

#endif //AIO_IMPORT_PARTICLE_H