#ifndef AIO_IMPORT_PARTICLE_H
#define AIO_IMPORT_PARTICLE_H

//lib4aio:
#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    template<typename T>
    class array_list;
}

struct aio_file;

using namespace lib4aio;

class aio_import_particle : public aio_particle<aio_file> {

public:

    explicit aio_import_particle();

    ~aio_import_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(aio_file *space);

private:

    array_list<str_hook> *import_list_ptr;
};

#endif //AIO_IMPORT_PARTICLE_H