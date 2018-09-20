#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

namespace lib4aio {

    template<class S>
    aio_orbit<S>::aio_orbit()
    {
        array_list<aio_particle<S>> *particle_list = create_particle_list();
        const unsigned list_size = particle_list->get_size();
        //Provide parent to children:
        for (unsigned i = 0; i < list_size; ++i) {
            const aio_particle<S> *particle = particle_list->get(i);
            particle->rotate_around(this);
        }
        this->particle_list = particle_list;
        this->mode = AIO_ALL_PARTICLES_SCAN;
    }

    template<class S>
    aio_orbit<S>::~aio_orbit()
    {
        this->particle_list->free_elements();
        delete this->particle_list;
    }

    template<class S>
    void aio_orbit<S>::reset_particles()
    {
        const unsigned list_size = particle_list->get_size();
        //Provide parent to children:
        for (unsigned i = 0; i < list_size; ++i) {
            const aio_particle<S> *particle = particle_list->get(i);
            particle->reset();
        }
    }

    template<class S>
    void aio_orbit<S>::illuminate(S space)
    {
        this->current_particle->illuminate(space);
        this->mode = AIO_ALL_PARTICLES_SCAN;
        this->current_particle = nullptr;
        this->reset_particles();
    }

    template<class S>
    S *aio_orbit<S>::launch(const str_hook *string_holder)
    {
        S *space = new_space();
        const unsigned particle_count = particle_list->get_size();
        const unsigned end = string_holder->end;
        const char *source_string = string_holder->get_string();
        this->position = string_holder->start;
        while (this->position < end) {
            const char symbol = source_string[this->position];
            switch (this->mode) {
                case AIO_ALL_PARTICLES_SCAN: {
                    for (unsigned j = 0; j < particle_count; ++j) {
                        const aio_particle<S> *particle = particle_list->get(j);
                        const aio_particle_signal signal = particle->handle_symbol(symbol);
                        if (signal == AIO_PARTICLE_SIGNAL_DETECTED) {
                            this->active_spider = particle;
                            this->mode = AIO_ONE_PARTICLE_SCAN;
                            break;
                        } else if (signal == AIO_PARTICLE_SIGNAL_IS_READY) {
                            this->illuminate(space);
                        }
                    }
                }
                    break;
                case AIO_ONE_PARTICLE_SCAN: {
                    const aio_particle<S> *particle = this->current_particle;
                    const aio_particle_signal signal = particle->handle_symbol(symbol);
                    if (signal == AIO_PARTICLE_SIGNAL_IS_READY) {
                        this->current_particle = particle;
                        this->illuminate(space);
                    }
                }
            }
            this->position++;
        }
        return space;
    }
}