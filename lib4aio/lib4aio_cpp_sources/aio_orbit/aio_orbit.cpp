#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>
#include <lib4aio_cpp_sources/aio_orbit/aio_particle/aio_particle.cpp>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

namespace lib4aio {

    template<class S>
    aio_orbit<S>::aio_orbit()
    {
        this->particle_list = create_particle_list();
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
            aio_particle<S> *particle = particle_list->get(i);
            particle->reset();
        }
    }

    template<class S>
    void aio_orbit<S>::illuminate(S *space)
    {
        this->iterator_position = this->current_particle->illuminate(space);
        this->mode = AIO_ALL_PARTICLES_SCAN;
        this->current_particle = nullptr;
        this->reset_particles();
    }

    template<class S>
    S *aio_orbit<S>::launch(const str_hook *string_holder)
    {
        S *space = new_space();
        const unsigned list_size = this->particle_list->get_size();
        //문자열 소유자를 놓다:
        for (unsigned i = 0; i < list_size; ++i) {
            this->particle_list->get(i)->set_scanning_string_holder(string_holder);
        }
        //스캔 시작:
        this->iterator_position = string_holder->start;
        while (this->iterator_position < string_holder->end) {
            switch (this->mode) {
                case AIO_ALL_PARTICLES_SCAN: {
                    for (unsigned i = 0; i < list_size; ++i) {
                        aio_particle<S> *particle = particle_list->get(i);
                        const aio_particle_signal signal = particle->handle_symbol(this->iterator_position);
                        if (signal == AIO_PARTICLE_SIGNAL_DETECTED) {
                            this->current_particle = particle;
                            this->mode = AIO_ONE_PARTICLE_SCAN;
                            break;
                        } else if (signal == AIO_PARTICLE_SIGNAL_IS_READY) {
                            this->illuminate(space);
                        }
                    }
                }
                    break;
                case AIO_ONE_PARTICLE_SCAN: {
                    aio_particle<S> *particle = this->current_particle;
                    aio_particle_signal signal = particle->handle_symbol(this->iterator_position);
                    if (signal == AIO_PARTICLE_SIGNAL_IS_READY) {
                        this->current_particle = particle;
                        this->illuminate(space);
                    }
                }
            }
            this->iterator_position++;
        }
        return space;
    }

    template<class S>
    S *aio_orbit<S>::new_space()
    {
        return nullptr;
    }

    template<class S>
    array_list<aio_particle<S>> *aio_orbit<S>::create_particle_list()
    {
        return nullptr;
    }
}